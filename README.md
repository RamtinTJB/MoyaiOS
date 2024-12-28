# MoyaiOS 🗿
I'm working on this operating system as a hobby to explore the foundational concepts of OS development. After taking CSE 120 at UCSD with Professor [Geoffrey Voelker](https://cseweb.ucsd.edu/~voelker/), I became really interested in Operating Systems, so I decided to make a simple one :)

P.S. It's called MoyaiOS because I really like the Moyai Emoji 🗿

## Current Features

These are the things I have developed so far (It ain't much but it's honest work):

- Stage 1 and 2 Bootloader
- VGA Text Driver

## Milestones
- [x] Bootloader and kernel initialization
  - [x] Write bootloader to load the kernel into memory
  - [x] Setup GDT and IDT
  - [x] Enable hardware interrupts
- [ ] Process Management
  - [ ] Impelement basic process creation, termination, and state transitions
  - [ ] Simple round robin scheduling algorithm
  - [ ] Context switching between processes
- [ ] Memory Management
  - [ ] Implement paging
  - [ ] Set up virtual memory for processes
  - [ ] Support for memory segmentation
  - [ ] Design kernel heap for dynamic memory allocation
- [ ] Concurrency
  - [ ] Lightweight threads within processes
  - [ ] Synchronization primitives (mutex, semaphore, condition variable)
- [ ] Support basic system calls

## Ambitious Features
These will most likely be too involved to implement for a hobby OS but who knows, maybe one day I'll get to them

- Graphics
- Networking (TCP/UDP over IP stack)
- Advanced scheduling
- Device drivers
- Security features
- Multi-core support
- Shell scripting
- Porting GCC to my OS

## Contributing

Contributions are welcome! Please fork the repository and cerate a pull request with detailed descrioptions of your changes. Since the project is in early stages, I don't really have a contribution guideline.

## License

The project is licensed under the [MIT License](https://opensource.org/licenses/MIT):

Copyright &copy; 2025 Ramtin Tajbakhsh
