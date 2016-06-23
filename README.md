## What is this?

Straightforward raytracing library in C++. It is single-core, nothing fancy - perfect for raytracing-novices to see theory implemented in practice. 

## Features

 * Geometry types
   * Infinite plane
   * Sphere
 * Light types
   * Sphere
 * Materials
   * Lambert
   * Mirror
 * Raytracers
   * Naive (first hit and done)
   * Pathtracer (with russian rulette + importance sampling).
 * Pixel sampling methods
   * Random
   * Jittered-grid
   * Adaptive
 * IO
   * Can load external XML configuration files
 
## Demo

The demo application under [demo/](demo/) takes xml configuration files through the command line (examples are found in [demo/config/](demo/config/)) and renders them into images. Rendering output of the sample configurations can be viewed under [demo/img/](demo/img/).

## License

This software is licensed under the **MIT License**. See the [LICENSE](LICENSE.txt) file for more information.
