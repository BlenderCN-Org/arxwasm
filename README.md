            _______________________
           /\                      \
           \_|         Arx         |
             |      Libertatis     |
             |   __(PNaCl port)____|__
              \_/____________________/

This is an experimental port of the Arx Libertatis project to Portable Native Client architecture (PNaCl) and Pepper API (PPAPI), allowing to run the Arx Fatalis game in a native sandbox of Google Chrome browser.

## Contents

* [Port Status](#port-status)
* [How To Run](#how-to-run)
* [How To Build](#how-to-build)
* [Technical Details](#technical-details)
* [FAQ](#faq)
* [Credits](#credits)
* [Contact](#contact)

## Port Status

**Working!** 

...although not yet completely playable due to one technical limitation.

### What is working

Almost all of the game subsystems are working flawlessly (rendering, audio, game logic, menus, save/load, etc.), and it is possible to play the game. 

The game runs smoothly in Chrome browser, embedded as a PNaCl module in a HTML page. It can be loaded directly from the Web, simply by loading an URL in the browser. There is no need to install a Chrome App, or use the Chrome Web Store. See section [How To Run](#how-to-run) if you want to give it a try.

The port have been tested with latest version of Chrome for Windows and Linux (starting from version 41), both on x86 and x86_64 architectures. I did not test with Chromebooks, or other ARM / MIPS based device. I'd be interested to know if this is working !


Please, note that even though Arx Libertatis source code and binary are freely usable, the original game data data is required to play the game. As this data is licensed under a commercial license, you will have to provide it using your own original copy of the game, or get it from the available game demonstration. 

See section [Access to game data](#access-to-game-data) for more information on this topic.

### Technical limitation

There is still one technical limitation that prevent 'real' gameplay for now: the _mouselook_ functionality does not work correctly, making navigation in the game 3D world quite difficult.

Note that keyboard navigation may still be used as a workaround (even though it is not practical for this game), and in-game menu/inventory mode as well as the specific mouse-based Magic gameplay works.

This limitation is due to a missing feature in the Native Client backend implementation of the SDL library: the mouse-locking mechanism provided by Pepper API is not correctly handled by SDL. Such feature is generally required by FPS games, as it allow to fully capture the mouse and simulate player view orientation.

So, with a few more work on SDL and Arx Libertatis it would be possible to overcome this issue. If someone is interested to take a look at this, I can provide more information.


## How to run

### Prerequisites

The latest stable version of Google Chrome Browser is required, which can be found here:

http://www.google.com/chrome/

Chrome is supported on Windows, Linux, and Mac OS X, on Intel x86 32-bit and 64-bit architectures. 

A few remarks:

- Although Chrome is supported on Android and iOS (both on ARM architecture), Native Client is not supported on these mobile operating systems for now.

- For some unknown reason, the open-source browser "Chromium" provided by Debian/Ubuntu distributions does not come with Native Client support by default. For now, you have to use Google Chrome instead (or build Chromium from sources yourself).

### Running the Game in the browser

The easiest way to see the game running in your browser is simply to go to the following URL using latest version Chrome: 

http://arxpnacl.cad-labs.fr

A static website is hosted here, with a main HTML page embedding the PNaCl module ready to run, and some Javascript code to provide browser-side access to game data.

#### Alternative methods

An alternative method to test this port is to run yourself a local HTTP server, delivering the same sample website. 

To do this, download a preview release from github: _arx-pnacl-preview-NNN.zip_, uncompress it, and execute the _run.sh_ script. 

It will start a simple HTTP server, configured to give access to the website content (located in 'www-root' subfolder). In this case, the following URL have to be used:

http://localhost:5100

Finally, you may also build the Native Client module yourself, and host it in a similar way. The source code of the sample website is fully available in git repository. See section 'How To Build' for more information. 

### Access to game data

In all cases, you will need the game data for anything to work !

This game data can be hosted on a local or remote server and accessed through HTTP, or provided directly by the user from its own local filesystem. This latter option uses the HTML5 Filesystem feature of Chrome, also used to store configuration files and saves locally.

Obviously, I do *not* provide any game data, as the game is licensed under a commercial license. 

So you have to provide the game data yourself, using your own original copy of the game, and use browser-side functionality of the website to allow the Native Client module having access to it. 

Here is how to do:

* Get your original copy of the game, or get the game demo

If you don't already own an original copy of the game, it can be bought for a reasonable price from well known digital stores (GOG, Steam, etc.).
If you like immersive RPGs and have ~30 hours available, don't hesitate: it is an enjoyable game (and really flawed too... but this is another story).

You may also use the game demo, available from the publisher. For the purpose of testing this port, it is a reasonable choice.

All information can be found here, including where to find the demo: http://wiki.arx-libertatis.org/Getting_the_game_data

* Extract game content

Once you have the game, you will need to extract its content: the __*.pak__ files. 

If you are on Windows, the easiest way to get this data is to install the game locally, and locate the .pak files in the installation folder. But for other systems (Linux), the method is different.

More information here: http://wiki.arx-libertatis.org/Installing_the_game_data_under_Linux

* Make the Native Client module access to the game data

There is two ways to do this: either locally through HTML5 filesystem feature of Chrome, or remotely through HTTP.

If you are running the game from the web, using the URL provided at beginning of this section, you have to use the first option.

* 
    * Option 1: Using the HTML5 filesystem

The process is straightforward: use the "Select Files" button in the main web page, and select all the *.pak files. They will be copied to a HTML5 filesystem from which the Native Client module will be able to read. 

Note this option will really duplicate game data to somewhere in Chrome cache, as Native Client modules ran from the Web can't have direct access to local filesystem (note: the Chrome Filesystem feature is only available to Chrome Apps and Extensions).

Once all data is copied (be sure to wait for all selected files to complete), simply click on "Launch Arx" button... and here you go: Arx Fatalis is running in your browser!

* 
     * Option 2: Access through HTTP

This method require to to host the website yourself.

In this case, copy all the *.pak files under a new 'arx' subfolder of the 'www-root' folder.

Upon access to localhost in the browser, the game will be loaded directly.

### A note on initial loading time

The first time the program is loaded, it will take quite some time to complete (with some visible "hang" around 95%). This is because PNaCl modules are compiled to native architecture from LLVM bytecode, and Arx Libertatis is almost 10MB in size. This is quite a lot.

## How to Build

Building consist in cross-compilation of Arx Libertatis and its dependencies to the Native Client platform, by using the NaCl SDK, the Naclports project, and this fork of the Arx Libertatis project.

As usual with cross-compilation, the most difficult part is to correctly install and  setup the build environment, and then build the project dependencies.

### Build Prerequisites

#### 1) Operating System

Building have been tested with the following Linux distributions: Ubuntu 12.04 LTS, Ubuntu 14.04 LTS, and Debian 8.

Note that Debian 7 is not working due to an outdated GNU libc (the NaCl SDK needs at least 2.15)

I did not test building on Windows and Mac OS X. Feel free to share experience on this.

#### 2) Installing the NaCl SDK

The NaCl SDK provide the core toolchains for NaCl and PNaCl (compiler, linker, standard header and libraries), and the Pepper API headers and libraries.

Here are the basic steps to install the SDK. More information may be found here: http://developer.chrome.com/native-client/sdk/download

* The following packages needs to be installed: python2.7, make, binutils, libc6:i386, libstdc++6:i386

        $ sudo apt-get install python2.7 make binutils libc6:i386 libstdc++6:i386
     
    The last two packages are only required if your distribution is based on a 64-bit architecture. 
      
    Note that Debian 64-bit will require some additional steps to be able to install 32-bit packages. Detailed information here: https://wiki.debian.org/Multiarch/HOWTO

* Download the NaCl SDK:

        $ wget http://storage.googleapis.com/nativeclient-mirror/nacl/nacl_sdk/nacl_sdk.zip
        
    If the direct link doesn't work, the SDK may be found on this page: http://developer.chrome.com/native-client/sdk/download

* Unzip the archive:

        $ unzip nacl_sdk.zip 

    __Important note__: do NOT have unicode characters in the SDK path. For unknown reasons some SDK scripts will fail otherwise.

* Run the following commands to install a version of the SDK:

         $ cd nacl_sdk
         $ ./naclsdk list
         $ ./naclsdk install pepper_<version>

    Replace "version" with the latest version flagged as being "stable" from the "list" command. For example, you may use version 42, which is a nice number.

* Finally, setup the NACL_SDK_ROOT environment vhariable:

        $ export NACL_SDK_ROOT=<path_to_nacl_sdk_folder>/pepper_<version>

    This is very important, as the rest of build instructions will rely on this environment variable. I highly recommend you to add this line to your .bashrc, and update it when you use a new version of the SDK. This will prevent you to do this everytime you start a new shell!

#### 3) Installing Naclports

The Naclports project provide an easy access to Native Client ports of well-known open-source applications and libraries. 
As most of Arx Libertatis dependencies have already been ported to Native Client, they are available out of the box in Naclports.

Here are the basic steps to install Naclports. More information may be found here:  http://code.google.com/p/naclports/wiki/HowTo_Checkout 

* If you come from the previous chapter, be sure to move outside the nacl_sdk folder:
            
        $ cd .. 

* The following packages needs to be installed: git, python2.7, python-dev, make, sed, bash, curl, zip

        $ sudo apt-get install git gcc python2.7 python-dev make sed bash curl zip

* For some reason, Naclport relies on "Depot Tools" to be installed. More information may be found here: http://www.chromium.org/developers/how-tos/install-depot-tools 

    As a summary, run the following commands:
     
            $ git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git
            $ export PATH=`pwd`/depot_tools:"$PATH"

* Now you can install Naclports, using the following commands:
    
            $ mkdir naclports
            $ cd naclports
            $ gclient config --name=src https://chromium.googlesource.com/external/naclports.git
            $ gclient sync
            $ cd src
            $ git checkout -b pepper_<version> origin/pepper_<version>

    Of course, replace "version" with whatever version of the SDK you installed in the previous chapter.
    
### Building the project dependencies

The library dependencies are of Arx Libertatis are: zlib, Freetype, SDL2, Boost, OpenAL, Regal (an OpenGL 1.x wrapper on top of OpenGL ES 2), and GLM.

Most of them are already ported to Native Client (with the exception of GLM), and part of the Naclports project. They are not always upstream, but it is sufficient for this Arx Libertatis port.

Here are the steps to build these libraries:

* Move into the naclports/src directory (if you come from the previous chapter, you should already be there):

        $ cd naclports/src

* The following packages needs to be installed: autoconf, automake, libtool, texinfo, gettext, pkg-config, xsltproc, cmake.
    
    These are build-time tools required by the various build systems of the projects.
    
        $ sudo apt-get install autoconf automake libtool texinfo gettext pkg-config xsltproc cmake
    
* To build for __Portable Native Client__, run the following commands:

        $ export NACL_ARCH=pnacl
        $ make zlib freetype sdl2 openal-soft regal boost 

    This may be quite long to build, but it will eventually complete.
Once a library is built, the NACL SDK is directly updated with the build result.

* [Optional] To build for __Native Client__ (that is, x86 or x86_64 architectures), use:

        $ export NACL_ARCH=x86_64
        $ make zlib freetype sdl2 openal-soft regal boost 
    
    Using a Native Client executable instead of Portable Native Client may be useful for debugging, and it allows faster compilation. However, be advised that such Native Client executables can't be run in Chrome without a special flag activated in the browser (this is because they are not architecture independant, hence not ready for the open web).
    
#### A note on GLM library

This library is not part of Naclports.
But as it is a header-only library, there is in fact nothing to be build externally.

For convenience, this library have been stored directly as a git submodule of the ArxLibertatis-pnacl project.

### Building ArxLibertatis-pnacl

Here is the final part, build ArxLibertatis Portable Native Client module:

* If you come from the previous chapter, be sure to move outside _naclports/src_ folder:
    
        $ cd ../..

* Fetch the source code of this fork of Arx Libertatis:

        $ git clone https://github.com/gabrielcuvillier/ArxLibertatis-pnacl.git
        $ cd ArxLibertatis-pnacl
        $ git submodule init
        $ git submodule update

    The last two lines are required to initialize the GLM library stored as submodule.
    
* Generate the makefiles using CMake, configured with the special toolchain file for PNaCl. Be sure to have build all the required dependencies, and setup the NACL_SDK_ROOT environment variable correctly.

        $ mkdir build_pnacl
        $ cd build_pnacl
        $ cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain-pnacl.cmake ..
        
    Check twice the name of the toolchain file: it is _toolchain-pnacl.cmake_
        
* Finally, build the final executable using:

        $ make
        
Once the build is complete, there will be two files generated:

* _arx.pexe_    
        
    This is the final Portable Native Client module (.pexe suffix). 
    It have been stripped and 'finalized' (see SDK docs about this concept).
    
    Such portable executables are intended to be loaded and executed in Chrome, directly from the Web, without any special flags activated.
           
* _arx.bc_      
        
    This one have been not finalized. It may be used for debugging pnacl code directly.

As portable native client executable might be quite big for the Web, there is an additional step you may want to consider:
        
        $ make pnacl-compress
        
This will compress the final arx.pexe executable, reducing its size by roughly 30%.

#### [Optional] building for Native Client (x86 or x86_64)

Like the project dependencies, it is possible to build ArxLibertatis for Native Client directly. A special toolchain file is provided for the x86_64 architecture. 

* The makefile generation can be done with the following commands:

        $ mkdir build_x86_64-nacl
        $ cd build_x86_64-nacl
        $ cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain-x86_64-nacl.cmake ..
        
    Check twice the name of the toolchain file, now it is _toolchain-x86_64-nacl.cmake_

* Then build the final executable:

        $ make
        
Once the build is complete, there will be two files generated:

* _arx_x86_64.nexe_    
        
    This is the final Native Client module (.nexe suffix), for x86_64 architecture.
    It have been stripped.
    
    **Important**: Contrary to Portable modules, these "unportable" ones can't be executed in the Browser by default. The special flag _#enable-nacl_ needs to be activated in Chrome to allow their execution.
           
* _arx_x86_64_unstripped.nexe_
        
    This one have been not stripped. It may be used for debugging native client code.
    

### Testing the build

Portable Native Client modules are executed in Chrome by embedding them in a HTML page delivered through HTTP.

For convenience, a static website that does exactly this have been created. It is located in the ___data/nacl___ subfolder of the project, and contains the following data:

* a _www-root_ subfolder, with the website content.

    This consists of the main HTML page embedding the Portable Native Client module (index.html), a native client manifest file (arx.nmf), as well as a support javascript file to provide browser-side access to game data (arx.js).
    
* a _run.sh_ script allowing to start a local HTTP server configured to give access to this www-root folder.

Note that this website is exactly the same as the one hosted at http://arxpnacl.cad-labs.fr

So, in order to test the build, just drop the generated Portable Native Client module (_arx.pexe_) in the _www-root_ folder, execute the _run.sh_ script from a terminal, and finally open Chrome to load the following URL:

http://localhost:5100

Once there, please refer to the [Accessing Game Data](#accessing-game-data) section for more information on how to setup game data (either by using the HTML5 filesystem, or accessing through HTTP directly).

Here it is, your compiled Arx Liberatis PNaCl module is now running in the browser!

Note it is possible to debug it using GDB, but this is another topic. Please, see the NaCl SDK documentation about how to debug PNaCl modules.

#### [Optional] Test for Native Client (x86 or x86_64)

If you have build for Native Client on x86_64, the way to test the build is almost the same. The differences are:

* This time, it is the Native Client module (_arx_x86_64.nexe_) that must be copied in the _x86_64_ subfolder of the _www-root_ folder.

* The URL to use in Chrome is:
    
    http://localhost:5100/x86_64
    
* ... and don't forget to activate the flag _#enable-nacl_ in Chrome.

You will notice that initial loading time is a lot faster than with PNaCl modules. However, overall program performance is the same afterward. 

## Technical Details

Even though most of dependencies were already ported thanks to the Naclports project, porting of the game itself required a wide variety of changes. Most notably:

* Build system
    * Updates to the existing CMake build system, to support cross-compilation to NACL and PNACL toolchains using NACL SDK and Naclports.
* Game source code
    * Specific initialization for backends, and various updates for them to work correctly (for example, disabling usage of GLEW).
    * Filesystem backend changes to access game data from HTTP or HTML5
    * Fix several compilation issues, or other warnings
* Support files
    * Sample website and JS scripts to host the PNaCl module, and provide browser-side access to game data

### Implementation notes

If you are interested to know more about the implementation details of this port, see the file IMPLEMENTATION_NOTES.NACL.md

## FAQ

### What is Native Client ?

Native Client (NaCl) is a sandboxing technology for running compiled C and C++ code at native speed in a secure sandbox. Portable Native Client (PNaCl) allow the compiled code to be architecture independent.

For now, this technology is used almost exclusively by the Google Chrome browser to run native applications embedded in web pages. But its usage could go beyond the browser.

For more information, see: https://developer.chrome.com/native-client

### Why this port ?

This port have been done mostly to learn the Native Client stack (toolchain, API, runtime, etc.), and evaluate if this technology is mature enough to support development of real moderately-sized C++ applications (and not only demonstration programs or benchmarks).

Arx Libertatis have been chosen because it is an open source project that fit the C++ project size requirement, with added bonus to have most of its dependencies already ported to Native Client. Also, it is a game I enjoyed in the past.

This porting effort also have been an opportunity to think about how this technology could be used beyond the browser. A couple of other projects already have found interesting ways to use it, for example the "Unvanquished" project (as a secure sandbox for native game plugins) or "ZeroVM" (for server-side single process virtualization).

For my part, I do think that Native Client could be used as a standard target platform for many desktop applications, and in particular CAD softwares. But this is another story that have yet to be written...

### 'Mouselook' is unusable!

Yes, this is _the_ most important limitation of this port. See section [Port Status](#port-status) and [Technical Details](#technical-details) for more information on this limitation, and how it could be solved.

## Credits

The Native Client team, for creating this interesting sandboxing technology.

Arkane Studios, for creating the Arx Fatalis game and released its source code under an open source license.

The Arx Libertatis team, for its impressive amount of work to enhance it.

## Contact
dev_at_gabrielcuvillier_dot_fr
