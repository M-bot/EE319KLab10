# Lab 10 - The Binding of RY (tentative)
Final Project for EE319K (Introduction to Embedded Systems), as of Spring 2016

The _The Binding of RY_ project combines the aspects of Labs 1-9 into a video game based off The Binding of Issac. The project includes an analog and digital input driver, audio driver, LCD driver, and graphics engine.

Current Roadmap:
- [x] Create Repository
- [x] Obtain Lab 10 Starter Files
- [x] ~~Implement 3D rendering (Progress can be seen [here](https://www.youtube.com/watch?v=6jVMg5p2KdE))~~
- [x] Select game idea
- [x] Implement 2D rendering
- [x] Create sprites
- [x] Implement input button logic
- [x] Implement audio logic
- [x] Build physical circuit
- [x] Implement movement logic
- [x] Implement firing logic
- [x] Implement collision logic
- [x] Implement enemy logic
- [x] Implement room logic
- [x] Implement input slide pot logic
- [ ] Create rooms
- [ ] Quality Assurance & Testing

Created by Miguel Obregon and Bryce Cotner


After a week of development we've determined a 3D engine for TM4C123* would be very limited or require months of optimizations due to memory constraints (and skill constraints). The TM4C123 family only has 32K RAM while a decent 3D engine needs at least 1M RAM. 
