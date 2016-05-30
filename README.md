# MotoMonkey
## Introduction
I wanted to find a solid data acquisition and telemetry system for track motorcycle riding. Like everything else, commercially available kits are either too expensive for feature rich models or too basic for lower cost models.  MotoMonkey is born. My goal for MotoMonkey is to create an open-source feature-rich data system that is low cost and can be built by anyone with some technical savvy.  

## Simple Requirements
1. Cheap, cheap, cheap - Price point to build a MotoMonkey will be about a few hundred bucks.
2. Extensible - attempt to make so that sensor integration can be customized and software can be tailored to individual needs.
3. Data rich - interfaces for the ECU and BlueTooth, sensors for inertial measurement, GPS, and generic IO (analog and digital) for custom sensors and interfaces.
4. Telemetry - need to do some exploration here - would really like the system to use an ad-hoc network - that may be too far to reach - a simple point to point radio model may be the most achievable.

## System Design
The MotoMonkey consists of two major pieces - 1) The on-board data acquisition system and 2) a ground station laptop.
![Alt text](https://cloud.githubusercontent.com/assets/3347351/15641098/427cf59a-25f3-11e6-8442-03b79fd1e716.png)

### On-Board Data Acquisition System
#### CPU/MCU
I have tentatively chosen the Intel Edison single-board computer for this project.  It is cheap and capable, has a number of built-in goodies (like wifi and low power bluetooth) and has a small form factor. A major discriminator is the built-in microcontoller unit (MCU) that allows the system to have real-time functionality without the addition of an external MCU. I have considered Arduino solutions (after all, the Arduino is an MCU), and I have convinced myself I want more processing capability. So, why not a Raspberry Pi? Simple - no real-time capability without external modifications. I actually started this project thinking of using the Pi - but my thinking evolved to the Edison based on the things listed above. I also considered using an Xilinx Zinq SoC FPGA + ARM, but reconsidered based on the project targeting DIYers and the added complexity of dealing with an FPGA.  Later iterations of project hardware may see an evolution to something more like a Zinq (if you are curious - the Adapteva line of Parallela single board computers may interest you).    

Tentative functions identified for the CPU (and not limited to):
- A true inertial navigation system (INS) with GPS aiding - the INS provides accurate orinetations, position and velocity information (this is in contrast to an attitude and heading reference system, or AHRS, that only provides orientations)
- High capacity data logging to a SD card
- Time synchronization with a GoPro

## Bill of Materials (BOM)
This table lists the parts I am using for the prototype - cost will come down when a PCB is designed and parts can be co-located on a single - compact board.

| Index | Item Name    | Description | Manufacturer | Part Number | Qty | Cost   | Total   |
| :---: | :--------    | :---------- | :----------- | :---------- | :-: | ---:   | ----:   |
| 1     | Intel Edison | CPU/MCU     | Intel        | N/A         | 1   | $50.00 | $50.00  |
| 2     | XBee Pro 900 | Data Link   | XBee         | N/A         | 2   | $55.00 | $110.00 |
| 3     | UBlox GPS    | GPS         | UBlox        | N/A         | 1   | $49.00 | $49.00  |
| 4     | AltIMU-10    | IMU         | Pololu       | N/A         | 1   | $23.00 | $22.00  |
|       |              |             |              |             |     | Total  | $231.00 |



## Installation
TODO: Describe the installation process

## Usage
TODO: Write usage instructions

## Contributing
1. Fork it!
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: `git push origin my-new-feature`
5. Submit a pull request :D

## History
TODO: Write history

## Credits
TODO: Write credits

## License
TODO: Write license
