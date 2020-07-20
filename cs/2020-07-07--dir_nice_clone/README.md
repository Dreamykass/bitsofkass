# dir_nice_clone

Basically, smarter copy. Clones stuff in source, to target directory.

The meat of the program is as such:

```c#
// traverse source, and create empty directories in target
RecreatingTree.RecreateTree(dirSource, dirTarget, logs);

// traverse target, deleting whole directories that don't exist in source
ReverseDirDeleting.ReverseDirDelete(dirSource, dirTarget, logs);

// the same as above, but files
ReverseFilDeleting.ReverseFilDelete(dirSource, dirTarget, logs);

// traverse source, counting the number of files
var count = TraverseCounting.TraverseCount(dirSource, dirTarget, logs);

// and the actualy meaty meat of the meat: traverse source...
// just copying files from source to target, if they don't exist in target
// copying and overwriting if they do exist, but size/length between them differs
// doing nothing, if size/length is the same
TraversingProper.TraverseProper(dirSource, dirTarget, count, logs);
```

But why? Well, I have recently disabled motherboard RAID 1 that I had on my system, and I needed something in the software to sorta emulate that.

More specifically, I needed something that would periodically copy files from drive X to drive Y. But just copying them manually with CTRL-C and CTRL-V is kinda bad, cause like, it takes forever, and is "dumb".

So I went on to look for software that'd do it for me... and that was super frustrating. I'd loved me some FOSS, or at least the F part of FOSS. But I couldn't realy find anything that'd also: work, and not be outdated as hell, or require some hacks, or ways to operate that clearly aren't the intended ways.

So I made this, yeah. It does precisely what I want.