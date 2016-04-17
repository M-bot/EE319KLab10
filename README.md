# Lab 10 - TBN
Final Project for EE319K (Introduction to Embedded Systems), as of Spring 2016

The _To Be Named_ project combines the aspects of Labs 1-9 into a video game. The project includes an analog and digital input driver, audio driver, LCD driver, and graphics engine. At the moment a game idea hasn't not been selected. 

Current Roadmap:
- [x] Create Repository
- [x] Obtain Lab 10 Starter Files
- [x] ~~Implement 3D rendering (Progress can be seen [here](https://www.youtube.com/watch?v=6jVMg5p2KdE))~~
- [ ] Implement 2D rendering
- [ ] Select game idea
- [ ] Create sprites
- [ ] Implement input (buttons and slide pot) logic
- [ ] Implement game logic
- [ ] Implement output (audio and rendering) logic
- [ ] Build physical circuit
- [ ] Quality Assurance & Testing

Created by Miguel Obregon and Bryce Cotner


After a week of development we've determined a 3D engine for TM4C123* would be very limited or require months of optimizations due to memory constraints (and skill constraints). The TM4C123 family only has 32K RAM while a decent 3D engine needs at least 1M RAM. 