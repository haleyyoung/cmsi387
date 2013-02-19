Linux
=======

Pre-OS software:

    linuxPreOS1.JPG and linuxPreOS2.JPG
    
    Description:
        The first file shows the grub interface in which the user can
        pick which kernel they would like to boot from, but if the user presses 'e',
        they can alter the commands which are run in the firmware while the computer
        is booting up. This is significant because the way the operating system boots
        up can be altered from this menu. This is the most tamper proof pre-os
        software in relation to the other two OS's because it only allows the user to
        pick from existing drives, there are no other options available.

Kernel File(s):

    linuxKernel.png
    
    Description:
        The linux kernel can be found in the /boot folder, its
        large size as well as the version number of linux on my machine give the
        impression that this file must be the kernel.

Startup Scripts/Config Files:

    linuxConfigFiles1.png and linuxConfigFiles2.png
    (couldn't fit all the files on the screen at once)
    
    Description:
        The configuration files are located int /etc/init and generally
        end with '.conf'.

First Process:

    linuxFirstProcess.png
    
    Description:
        Under the PID column, the first process can be seen, its
        command name is 'init'. This makes sense since the configuration files are
        in the /init folder.

Network Settings:

    linuxNetworkSettings.png
    
    Description:
        This just shows a dialog box where the network settings can be
        altered.

=======

Windows
=======

Pre-OS software:

    windowsPreOS.JPG
    
    Description:
        This menu allows the user to toggle between different options
        for the configuration of the preboot environment as well as other variables.
        From this menu, a user can alter the boot process which occurs, but they
        don't have as much freedom as a linux user given that they are only allowed
        to toggle between options.

Kernel file(s):

    windowsKernel.png
    
    Description:
        The description says NT Kernel and System. Also, this is a
        large file, so it appears to be the kernel.

Startup scripts/config files:

    windowsStartupScripts.PNG
    
    Description:
        This dialog box is opened by running 'msconfig'. The boot tab shows the
        operating system, so I would assume the script tab shows the startup
        scripts.

First Process:

    windowsFirstProcess.png
    
    Description:
        The PID's start at 4, but the image name of the 4th process says
        'System' which would make sense as being the first process.

Network Settings:

    windowsNetworkSettings.png
    
    Description:
        This shows a dialog box where the preferences of the network
        connections can be changed.

=======

Mac OS X
=======

Pre-OS software:

    macPreOS.JPG
    
    Description:
        This picture shows the drive "zorl 0". The firmware is programmed
        to ask which drive you would like to boot from. Because this computer only had
        one drive to choose from, that was the only drive shown. Once a drive has been
        chosen, the firmware loads up that kernel and continues rebooting.

Kernel file(s):

    macKernel.png
    
    Description:
        The kernel is named Mach, so the mach_kernel file seemed
         appropriate. Its size also seemed large enough to be a kernel.

Startup scripts/config files:

    macConfigFiles.png
    
    Description:
        The startup scripts and config files generally have 'rc' and
        'config' somewhere in their file name, but the whole /etc folder is
        technically the startup scripts and config files.

First Process:

    macFirstProcess.png
    
    Description:
        The first process can be seen at the bottom of this picture, its
        command name is 'launchd'.

Network Settings:

    macNetworkSettings.png
    
    Description:
        This is just a dialog box where the nextwork settings can be
        tinkered with.
