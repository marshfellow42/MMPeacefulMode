import subprocess, os, shutil, json, zipfile, re, tomllib, pathlib, sys, platform
from pathlib import Path


PROJECT_ROOT = Path(__file__).parent

MOD_TOML_FILE = PROJECT_ROOT / "mod.toml"
MOD_DATA = tomllib.loads(MOD_TOML_FILE.read_text())

BUILD_DIR = PROJECT_ROOT / "build"
BUILD_NRM_FILE = BUILD_DIR / f"{MOD_DATA['inputs']['mod_filename']}.nrm"

RUNTIME_DIR = PROJECT_ROOT / "runtime"
RUNTIME_MODS_DIR = RUNTIME_DIR / "mods"
RUNTIME_NRM_FILE = RUNTIME_MODS_DIR / f"{MOD_DATA['inputs']['mod_filename']}.nrm"

ASSETS_ARCHIVE_PATH = PROJECT_ROOT / "assets_archive.zip"

USER_CONFIG_PATH = PROJECT_ROOT / "user_build_config.json"
if not USER_CONFIG_PATH.exists():
    USER_CONFIG = {
        "mod_compiling": {
            "compiler": "clang",
            "linker": "ld.lld"
        }
    }
    USER_CONFIG_PATH.write_text(json.dumps(USER_CONFIG, indent=4))
else:
    USER_CONFIG = json.loads(USER_CONFIG_PATH.read_text())

PACKAGE_DIR = PROJECT_ROOT / "thunderstore_package"
DIST_DIR = PROJECT_ROOT / "dist"


def run_build(args: list[str]):
    make_run = subprocess.run(
        [shutil.which("make")] + args,
        cwd=PROJECT_ROOT
    )
    if make_run.returncode != 0:
        raise RuntimeError("Make failed!")


def copy_if_exists(src: Path, dest: Path):
    if src.exists():
        shutil.copy(src, dest)
        print(f"Copied '{src}' -> '{dest}'")
        return True
    else:
        print(f"Missing file: {src}")
        return False


def copy_to_runtime_dir():
    os.makedirs(RUNTIME_MODS_DIR, exist_ok=True)
    portable_txt = RUNTIME_DIR / "portable.txt"
    if not portable_txt.exists():
        portable_txt.write_text("")
    copy_if_exists(BUILD_NRM_FILE, RUNTIME_NRM_FILE)


def slugify(text: str) -> str:
    text = text.strip()
    text = re.sub(r"[\s_]+", "_", text)
    text = re.sub(r"[^a-zA-Z0-9_]", "", text)
    return text


def get_website_url():
    if "website_url" in MOD_DATA["manifest"]:
        return MOD_DATA["manifest"]["website_url"]

    result = subprocess.run(
        [shutil.which("git"), "config", "--get", "remote.origin.url"],
        cwd=PROJECT_ROOT,
        capture_output=True,
        text=True
    )

    if result.returncode == 0:
        return result.stdout.strip().removesuffix(".git")
    return None


def get_package_manifest():
    raw_deps = MOD_DATA["manifest"].get("dependencies", [])

    deps = []
    for dep in raw_deps:
        if ":" in dep:
            name, version = dep.split(":")
            name = name.replace("_", "-")
            dep = f"{name}-{version}"
        deps.append(dep)

    return {
        "name": slugify(MOD_DATA["manifest"]["display_name"]),
        "version_number": MOD_DATA["manifest"]["version"],
        "website_url": get_website_url(),
        "description": MOD_DATA["manifest"]["short_description"],
        "dependencies": deps
    }


def create_manifest(path: Path):
    manifest = get_package_manifest()
    path.write_text(json.dumps(manifest, indent=4))
    return manifest


def update_manifest(path: Path):
    manifest = get_package_manifest()
    del manifest["name"]
    del manifest["dependencies"]

    current_manifest = json.loads(path.read_text())
    current_manifest.update(manifest)
    path.write_text(json.dumps(current_manifest, indent=4))
    return current_manifest


def create_readme(path: Path):
    content = f"# {MOD_DATA['manifest']['display_name']}\n\n{MOD_DATA['manifest']['description']}"
    path.write_text(content)


def create_archive(src_dir: Path, dst_path: Path):
    with zipfile.ZipFile(dst_path, "w") as z:
        for i in os.listdir(src_dir):
            if i == "images":
                continue
            z.write(src_dir / i, i)


def create_package():
    run_build(["post-build"])

    os.makedirs(PACKAGE_DIR, exist_ok=True)
    os.makedirs(DIST_DIR, exist_ok=True)

    manifest_path = PACKAGE_DIR / "manifest.json"
    if manifest_path.exists():
        manifest = update_manifest(manifest_path)
    else:
        manifest = create_manifest(manifest_path)

    readme_path = PACKAGE_DIR / "README.md"
    if not readme_path.exists():
        create_readme(readme_path)

    icon_ok = copy_if_exists(PROJECT_ROOT / "thumb.png", PACKAGE_DIR / "icon.png")
    mod_ok = copy_if_exists(BUILD_NRM_FILE, PACKAGE_DIR / BUILD_NRM_FILE.name)

    if icon_ok and mod_ok:
        print("Packaging mod...")
        out_zip = DIST_DIR / f"{manifest['name']}-{manifest['version_number']}.thunderstore.zip"
        create_archive(PACKAGE_DIR, out_zip)
        print(f"Done → {out_zip}")
    else:
        print("Missing required files; package not created.")


if __name__ == "__main__":
    create_package()
