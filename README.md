# Lapiz

Port of [SiraUtils](https://github.com/Auros/SiraUtil) features to Quest.

### What is Lapiz?

Lapiz is a library that abstracts the more difficult and tedious parts of [Zenject](https://github.com/modesttree/Zenject) away from you, making your life easier. The goal of Lapiz is to make features more accessible, and have Dependency Injection more a staple feature of Quest Beat Saber mods.

### When is this going to release?

Lapiz is nowhere close to stable, and therefore not ready for release. We are still working on implementing [Zenject](https://github.com/modesttree/Zenject) and the other important wrapper and providers.

### I got this installed... Do I need it?

Probably! There might be mods that require it and uses its providers or its features to make their mod work!

## For Developers

Zenject can be tedious to do in C++, especially if you don't know how to do this stuff. If you need help, please do send a message in #quest-mod-dev in [BSMG](discord.gg/beatsabermods) and I will get back to you as soon as I'm able.

With that out of the way, this is how you use Zenject through Lapiz.

First, you'll need an installer class. To do this, we'll use Custom Types.

```cpp
#include "custom-types/macros.hpp"
#include "GlobalNamespace/Zenject/IInstaller.hpp"

DECLARE_CLASS_CODEGEN_INTERFACE(Lapiz, MenuInstaller, classof(Zenject::IInstaller*),
    DECLARE_OVERRIDE_METHOD();
    DECLARE_OVERRIDE_METHOD();
)

```

To properly install the installer class we just made, you need to use the first of these provided install methods.

```cpp
#include "Lapiz/Zenjector.hpp"
#include "Lapiz/Location.hpp"
#include "installers/MenuInstaller.hpp"

// First you need to get a Zenjector instance.
auto zenjector = Zenjector::Get();

// Used together with an installer class
zenjector->Install<Lapiz::MenuInstaller*>(Location::Menu);

// Used as a standalone installer for smaller things, to reduce file clutter.
zenjector->Install(Location::Menu, [](Zenject::DiContainer* container){
    // container-> is used to access the DiContainer address,
    // where you can install anything you need.
    container->BindInterfaceAndSelfTo<Lapiz::MenuInstaller*>()->AsSingle();
});
```

Do note that this is very much preliminary documentation, and that more in-depth docs will come as a part of the final release.

## Contributing?

Fork the repo, make your changes and Pull Request it!

Follow [the contributing guidelines found here](/CONTRIBUTING.md)
