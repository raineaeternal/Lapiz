# Lapiz

Quest (Android/il2cpp) Beat Saber mod library exposing Zenject DI utilities to other mods. See `README.md` for the public-facing pitch.

## Build

CMake + Ninja, targeting `arm64-v8a` via the Android NDK. `qpm_defines.cmake` needs an NDK path, resolved in this order: `-DCMAKE_ANDROID_NDK`, `./ndkpath.txt`, `$ANDROID_NDK_HOME`, `$ANDROID_NDK_LATEST_HOME`.

```sh
export ANDROID_NDK_HOME=/path/to/ndk
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=RelWithDebInfo
cmake --build build
```

Builds two shared library targets (see `CMakeLists.txt`'s `shared_setup()` function):
- `lapiz` (`liblapiz.so`) — the real mod, built from `src/**/*.cpp` excluding `src/test/`.
- `test-lapiz` (`libtest-lapiz.so`) — an on-device test mod, built from `src/test/*.cpp`, linked against `lapiz`.

## Testing

Modeled on `beatsaber-hook`'s `src/tests` pattern. Lives entirely in `src/test/`:
- `tests.hpp` — `TEST(name)` registers a function into a global `tests` vector (via `__attribute__((constructor))`); `LOG_OK`/`LOG_FAIL` wrap the existing `INFO`/`ERROR` logging macros.
- `main.cpp` — the `test-lapiz` mod's own `setup`/`late_load` exports; `late_load()` runs every registered `TEST()`, catching exceptions per-test.
- Test files freely use Lapiz's affinity hook macros (`MAKE_AFFINITY_HOOK`, `MAKE_AFFINITY_HOOK_INJECTED`) and can install them onto a live Zenject container from inside a `TEST()` — see `gamecore_hook_test.cpp`.
- `mod.tests.json` packages `test-lapiz` as its own installable qmod, bundling the locally-built `liblapiz.so` directly as a `modFiles` entry (not a qpm dependency/download) so it always runs against the build you just made. Zip it with the `tests` qpm workspace script (`qpm.json`).
- These are **on-device** tests: no host-side test runner exists or is practical, since everything depends on live il2cpp/Zenject game state. Compiling + linking is the only thing verifiable off-device; actually observing pass/fail requires deploying to a Quest and reading logcat.

### `Zenjector::Get()` self-initializes — don't add your own init boilerplate

`Lapiz::Zenject::Zenjector::Get()` (`src/zenject/Zenjector.cpp`) calls `extern "C" void load();` internally before doing anything else. That symbol resolves at the dynamic-linker level to the *one* `load()` exported by `liblapiz.so` (guarded by a `loaded` bool, so it's a no-op after the first call), which runs `Hooks::InstallHooks()`, `i2c::functions::initialize()`, and `custom_types::Register::AutoRegister()`.

Practical implications:
- Any code in *any* mod loaded alongside `lapiz` (e.g. `test-lapiz`) can call `Zenjector::Get()->Install(...)` safely from anywhere — a `TEST()` run during `late_load()`, a hook body, whatever — without needing its own `load()` export or manual `AutoRegister()`/`initialize()` calls first. Order relative to the real Lapiz mod's own `load()` doesn't matter.
- Don't add `i2c::functions::initialize()` + `custom_types::Register::AutoRegister()` to a secondary mod target's own `load()` "just in case" — it's redundant. `AutoRegister()` drains a single process-wide pending-registration list; every loaded mod's `.so` already added its custom types to that list at `dlopen` time (before any mod's `load()` runs), so whichever mod calls `AutoRegister()` first picks up everyone's types.

## Known WIP gaps (branch `feat/affinity`)

The affinity-hook system (`shared/affinity/`) is new and under-exercised — several latent bugs have only surfaced once code actually instantiated the relevant templates or ran the relevant methods for the first time (e.g. `AffinityHookBuilder::install()`, `HookHandle::Initialize`/`Dispose`). If you touch this area and hit a compile error in code you didn't write, check whether it's simply the first real caller of that path before assuming it's something you broke.
