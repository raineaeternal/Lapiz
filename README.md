# `z`
Port of [SiraUtils](https://github.com/Auros/SiraUtil) features to Quest.

### What is `z`?
`z` is a library that abstracts the more difficult and tedious parts of [Zenject](https://github.com/modesttree/Zenject) away from you, making your life easier. The goal of `z` is to make features more accessible, and have Dependency Injection more a staple feature of Quest Beat Saber mods.

### Why `z`?
`z` is just a codename for the library. Name will be revealed closer to when the library is stable.

# Contributing?

Fork the repo, make your changes and Pull Request it!

  * Read under for guidelines on PRs.

# Submitting a Pull Request?

* Namespace your code by folder
* Lowercase namespace (`z::`)
* Follow the Clang format
    * CLion does this automatically, no need to do anything.
    * Download the Visual Studio Code clang extension and make a `.clang-format` file with the configuration under.
* When we request changes, you have 1 week to respond. If not we will dismiss the PR, and close it.

```clang
# Style "cscpp"
# global for actions
BasedOnStyle: LLVM
AllowShortBlocksOnASingleLine: true
AllowShortCaseLabelsOnASingleLine: true
AllowShortIfStatementsOnASingleLine: true
Cpp11BracedListStyle: true
IndentWidth: 4
NamespaceIndentation: All```
