# fuse_example
A minimalistic fuse example ( inspired from [ FUSE Tutorial ](https://maastaar.net/fuse/linux/filesystem/c/2016/05/21/writing-a-simple-filesystem-using-fuse/) )

## Building the code
To build the code, ```gcc s_fs.c -o sfs `pkg-config fuse --cflags --libs` ```

## Trying out the file system.

Now, as this is a very minimalistic approach, everything is pretty hardcoded and restricted. The functionalities suuported being,
  1. getattr ( similar to stat )
  2. [ readdir ] ( http://man7.org/linux/man-pages/man3/readdir.3.html )
  3. [ read ] ( https://linux.die.net/man/3/read )

Hence, this is ore of a read only file system being implemented here. To try out the filesystem you've just created, just run the code, ```./sfs -f ./mountpoint ```

Now, the -f option allows us to see the printf statements which we've mentioned in the code. The mountpoint is just a file wherein we want to point our custom file system. Now one can give any name to it. (There is no sound reason behind me calling it mountpoint other than laziness ).

Once you execute this, the file system will be mounted in the specified path. To verify, one can navigate through the file system to the given path wherein it was mounted, and also read the contents. Paralelly, one can notice the debug comments being displayed wherein the executable is being run.

> NOTE : Tread carefully ahead while modifying the code as well as executing it. I recommend not going a super user unless and until one is confident enough and has the know-how.

