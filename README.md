# TPExtended
##### A series of QoL patches for Treasure Planet: Battle at Procyon.
With these patches, the game runs smoother and is in a more playale and enjoyable state. 

### Features
 Mouse fixed when using high Polling rate (above 125hz)

- Multiclient Support
- Fixed no borders when in Windowed mode.
- Removed FPS Limit when tabbed out.
- Define Windowed Resolution. (default locked at 800x600)
- Resize Window

### Usage
1) Build the Debug version of the project using Visual Studio or download the precompiled .dll from the Releases.
2) Copy the compiled proxy ddraw.dll to the game folder (where tp_win32.exe is located) 
3) (Optional) Launch the game using the ``-Width:<width> -Height:<height>`` paramaters to defined the resolution in Windowed Mode, if no resolution is defined, it's defaulted to launch at 1920x1080. For Multiclienting, launch your subsequent clients with the paramter ``-Multiclient``.
4) Profit.

### To do
- Fix choppy camera when rotating around your ship.
- Unbind/Change the behaviour of zooming into your ship when right clicking.
- Other community requested fixes like Object World Limit, AI Ship Blacklisting.
