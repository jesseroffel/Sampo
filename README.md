# Sampo Game Framework

Personal project due to interest in Game Engine technologies, where I provide a simple to write decoupled API that can run multi-platform on selected targets which contains minimal but essential components to quickly start developing a new project and aid fast iterations. 

This project is expected to contain a minimal feature set by the end of `2020` and largely complete by the end of the academic year `2021`. Delays are expected to happen for whatever reason.

The framework design takes inspiration or ideas from exciting engines or frameworks such as the `Stingray`, `Unity`, `Unreal`, `Hazel` and `Osmium`.





## Learning goals

- Create a 2D `(and 3D in the future)` multi-platform game framework from scratch to gain more low level game programming knowledge and to create modern variants of classic games genres.
- Use programming patterns from books like: `Effective Modern C++` and `Game Engine Architecture`.
- Have the project available to be build using modern `CMake` and `Premake5` practices.
- Provide continuous integration checks using GitHub's `workflows` and provided Unit Testing.
- Have core components be decoupled and abstracted by platform where required.



## Components and features

There is a long list of subjects that I would like to learn about and work out myself as a challenge, realistically I can't do everything myself and so I'll also delegate as much as possible where I don't have much interest in or to safe essential time.



### Planned to be implemented

This list contains high level concepts that will be selected and worked on during the span of the project.

* Main entry point / PCH / Definitions
* Platform API abstractions
* Custom memory allocations
* Web sockets / HTTP requests
* Console Application / Logging
* Game Input abstractions
* Event handling / Application layers
* Debugging feature set / Diagnostics
* Error / Assert handling
* Hashing and `UTF-8` string handling
* Algebraic error types / Asserts
* Threading / Concurrent Programming
* Configuration Handling
* Asset compilation / Resource managing
* File System handling



### Delegated to third-party libraries/implementations

* Rendering API Abstractions / Window Creation
* Shader assets
* ImGui Implementation
* Data Oriented Design / Entity System
* JSON / TOML Parsing
* Receiving Input from hardware
* Common Mathematics: Vector, Quaternion etc. (Own implementation might follow)
* Resource asset data reading
* CI Framework / Unit Testing Framework




