# Paganini DAW

## Goal:

The goal with this project is to learn how to do proper desktop application structure in idiomatic C++. I want to be
able to extend this project easily when I have the time so that I have to do *minimal* backtracking or
reverse-engineering.

## Behind the Scenes:

The application will have a list of base classes. These classes will be in `src/core` and will be referenced (and made
polymorphic) a lot. The base classes in question are:

- `paganini::system`: a building block for providing functionality to other parts of the app.
- `paganini::entity`: elements that are owned by the app and that act as a handle to constituent components.
- `paganini::component`: attachments to entities that give them special properties.

Some notes:

- Entities behave like wrappers over a `std::vector` of `component *`'s. They pipeline the initialization and updating
  of components and are the main front-face for them to systems, the application, etc.
- Components provide functionality to entities. They give them renderable textures, rectangular shapes, audio buffers,
  etc. They are gathered by systems and used in systems' update cycle.
- Systems provide these functions:
  - To make sure file handles, large buffers, and other expensive objects are managed well, systems hold allocated
    resources for graceful deletion. 
  - A system is attached to the app, starts, updates, and stops.
  - A view into the application's active entities.
- Updates and plugins can be written as a custom system with new entities and components.
- Some packages that need to be installed can be installed on Linux-based systems using:
```bash
sudo apt-get install build-essential libxmu-dev libxi-dev libgl-dev libglfw3-dev libopenal-dev
```
- When including OpenAL headers, make sure to `#include <al.h>`. The exact path for the header's include varies between
  platforms, but CMake exposes it directly in each case.

## Progress:

- [x] `system`, `entity`, and `component` drafted - now made better!
- [x] Window displaying
- [x] Input system
- [x] Renderer system
- [ ] Audio system
- [ ] UI system
- [ ] Track editor
- [ ] MORE!!!
