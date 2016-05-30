# MotoMonkey
## Introduction
I wanted to find a solid data acquisition and telemetry system for track motorcycle riding. Like everything else, commercially available kits are either too expensive for feature rich models or too basic for lower cost models.  MotoMonkey is born. My goal for MotoMonkey is to create an open-source feature-rich data system that is low cost and can be built by anyone with some technical savvy.  

### Simple Requirements
1. Cheap, cheap, cheap - Price point to build a MotoMonkey will be less than a couple hundred bucks.
2. Extensible - attempt to make so that sensor integration can be customized and software can be tailored to individual needs.
3. Data rich - interfaces for the ECU and BlueTooth, sensors for inertial measurement, GPS, and generic IO (analog and digital) for custom sensors and interfaces.
4. Telemetry - need to do some exploration here - would really like the system to use an ad-hoc network - that may be too far to reach - a simple point to point radio model may be the most achievable.

### Starting Point
I have two goals in mind, first - a data and TM kit with quality software, second - provide a comprehensive blueprint for taking a prototype design to a higher level.  

I am going to base the MotoMonkey on a readily available single-board computer, the Raspberry Pi 2.  Sensors will be selected from items readily available to the hobbyist.  I will use KiCAD to create the schematics for a custom interface PCB, and I will have the PCB manufactured through one of many inexpensive prototyping services.  Finally, I will create a low-rate production-ish mechanical housing by 3D printing a housing mold and then casting the housing using a pourable urethane.  The end product should be pretty sweet. Hopefully you will find this project informative, and maybe a possible source for inspiration on your next project.

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
