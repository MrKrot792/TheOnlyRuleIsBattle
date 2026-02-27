# What is TORIB
Torib - is an open-source, turn based, TUI prototype for an online game that I will, maybe make someday.
And yeah, it's abandoned. Who could've saw that comming. Tho PRs are still accepted, and you could try making your own moves (in the `src/game.c`).
Maybe I'll comeback to this project, someday? But it'll probably be easier to just rewrite it completely.
So yeah, if it is being rewriten, I'll update the `README.md`.

# How-to build
TORIB uses meson, so building it is straightforward:
```bash
meson setup build
ninja -C build
```

And then run the game:
```bash
./build/torib
```
