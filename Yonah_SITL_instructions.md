# Instructions on compiling and running Ardupilot firmware on SITL

This set of instructions shows how to compile custom Ardupilot firmware to be tested in SITL. There are three steps: (1) Compile the firmware, (2) Launch SITL, (3) Connect MAVProxy to SITL

The instructions are tailored to Yonah's use case: Running quadplane AUTO testing at locations such as Kompiam Airfield.

## 1. Compiling

Navigate to your ardupilot repository folder, i.e. `cd <path to ardupilot repository>`

Before compiling, make sure the submodules are up to date. This is important if you have recently switch to a new branches, and there are updates to the submodules:

```sh
git submodule update --init --recursive
```

To compile, follow the instructions in [Build.md](https://github.com/ArduPilot/ardupilot/blob/master/BUILD.md). For example:

```sh
./waf configure --board sitl # Target the board for SITL
./waf plane # Compile the firmware into an executable
```

waf will then compile. If this is the first time compiling, it will take a while.

Once compilation is complete, the resulting executable will be found in `<path to your Ardupilot repository>/build/sitl/bin`

Within that folder, you will find an `ArduPlane` executable. **This is where you will run SITL from**.

*(Note: If you were compiling for a non-SITL target -- for example, CubeBlack -- then the resulting folder will be `<path to your Ardupilot repository>/build/CubeBlack/bin`, and the resulting "executable" will be `ArduPlane,apj`; this is the file that you flash into your flight controller)*

## 2. Running SITL

From your ardupilot folder, navigate to the folder containing the ArduPlane executable, and then run it. For Yonah's use case:

```sh
cd build/sitl/bin
./arduplane --model quadplane
```

By default, this starts SITL at the location CMAC. To start at a custom location, enter the coordinates using the `--home` flag, in the following format:

```sh
./arduplane --model quadplane --home <lat, long, height (MSL), initial bearing>
```

For example, the following command `./arduplane --model quadplane --home -5.38333333,143.92250000,1577,50` starts SITL at Kompiam airfield, at an MSL altitude of 1577m and a bearing of 50 degrees

If SITL starts up correctly, you should see the following commands:

```sh
Creating model quadplane at speed 1.0
Home: -35.363261 149.165235 alt=584.000000m hdg=353.000000 # Default CMAC location; this may change depending on what location you specify
Starting sketch 'ArduPlane'
Starting SITL input
Using Irlock at port : 9005
bind port 5760 for 0
Serial port 0 on TCP port 5760
Waiting for connection ....
```


## 3. Running MAVProxy and connecting it to SITL:

MAVProxy connects to SITL through a TCP connection over 127.0.0.1, port 5760. **In a new terminal**, start and connect MAVProxy with the following command:

```sh
mavproxy.py --master=tcp:127.0.0.1:5760
```

You can then load neccessary modules (e.g. map, console) to double check whether the connection to SITL has been successful.

If connection is successful, the resulting setup can be used to run SITL as per normal. Note that **all subsequent commands (e.g. arming, mode change) should be sent through the terminal runnning MAVProxy, not the terminal running SITL**


## 4. Using scripts to make life easier

Having to memorize complex commands is difficult. Here are some ways to make life easier using scripts/symbolic links:

### 4a. Symbolic Linking of arduplane executable

Use a [symbolic link](https://kb.iu.edu/d/abbe) to access the ArduPlane executable, instead of having the use the `cd` command all the time. For example, you can navigate to any folder where you want to run MAVProxy. Then from there, run the following command:

```sh
ln -s <path to Ardupilot repository>/build/sitl/bin/arduplane
```

This then establishes a symbolic link which manifests in your current folder as `arduplane`. You can then call this link directly instead of having to `cd` into the neccessary folder.

### 4b. Using bash scripts to abstract startup commands

[Bash scripts](https://www.taniarascia.com/how-to-create-and-use-bash-scripts/) are very powerful tools to abstract a complex set of commands. For example, to abstract the command `./arduplane --model quadplane --home -5.38333333,143.92250000,1577,50`;

1. Create a bash script e.g. `nano start_quadplane_Kompiam.sh`
2. Copy-paste the above command into the bash script
3. Save the file
4. Do `chmod +x start_quadplane_Kompiam.sh` to make the script executable
5. From now on, you can simply run `./start_quadplane_Kompiam.sh` to start SITL at Kompiam airfield

The same can also be done for complex MAVProxy startup commands (e.g. `mavproxy.py --master=tcp:127.0.0.1:5760 --console --map`)

## 5. Summary

* To build: `./waf configure --board sitl` followed by `./waf plane`
* To start SITL:
    * Navigate to where the SITL ArduPlane executable is located: `cd <path to your Ardupilot Repository>/build/sitl/bin`
    * Launch SITL: `./arduplane --model quadplane`
* To start MAVProxy and connect it to TCP: In a new terminal, type `mavproxy.py --master=tcp:127.0.0.1:5760`