# superdisplay

## General Information:
Author: Kai Pearson  
Date: Mar 19th, 2026  
Email: kaipearson@dal.ca  

## Import Information:

To meshes into the world, use the command `import` command. `import` can be used on individual .txt files or on folders full of meshes.  

For instance, `import ./meshfolder/` will import all meshes in `meshfolder`, while `import ./meshfolder/cube.obj` will import only the `cube.obj` file.

Please note that the directory starts from wherever the `superdisplay.exe` file is located.

## The .obj File Type

.obj is a file type made by Wavefront, and is the primary exported file type for 3D rendering software (such as Blender).

superdisplay supports the .obj file type and can render most imported .obj files, but it's important to recognize that only certain prefixes are recognized.

### Supported Prefixes
- v x y z (defines a vertex at point (x,y,z))
- f a b c (defines the face of a triangle with indexed vertices)
- o name (defines a name for the mesh)
- mtllib filelocation (using material files)
- usemtl material (using a temporary material)

### Unsupported Prefixes
- vt u v (texture coordinate)
- vn nx ny nz (normal coordinate)
- g name (group naming)
- s 1/0 (smoothing on or off)