# utxghost
Hiding your login activity from utmpx records

## Affected programs
Non-extensive list:
- `last`
- `lslogins`
- `users`
- `who`

## Non-affected programs
Non-extensive list:
- `loginctl`
- - uses a different mechanism
- `lastlog`
- - apparently not used on Arch Linux
- - not implemented
- `lastlog2`
- - uses a very different database system

<hr>

## FAQ
### Why though?
I have remote access over SSH to a friend's machine *with my own user account*, and they like to check when I logged in the last time (using `last`) - only to find out I haven't done so in at least a month and then complain about it.
So I decided to make a program that removes my entries from whatever database `last` reads, making its output worthless. Just removing the file would also remove any other entry and that isn't the goal.

It's a very niche use-case since you normally don't want to remove any logs like these, and it requires you to have a dedicated user account too.

### Can I use this to hack the mainframe and stay under the radar? 😎
No.

### How portable is it?
It works on Linux, but it *should* theoretically work on any Unixoid desktop system. The practical limitations are default file paths in `src/utx/sysfiles.c` since they aren't defined in `utmpx.h` and differ between OSes. So it's just Linux, FreeBSD, NetBSD and DragonflyBSD. However, I only tested this on Linux.

I couldn't find anything for OpenBSD. Apparently it doesn't even implement the `utmpx.h` interface. I also don't have a working installation of OpenBSD to check for myself.

<hr>

## Development
### Issues
I was going to implement this with a daemon mode too, so that I don't have to enter my password every time I logoff, but I decided to scrap it. Just adding my user to the `utmp` group would be way easier than implementing a system daemon that then also has to handle authentication (and doing all of this in portable C too).

C isn't a bad language by itself, but it really sucks when you want to use something that feels barely standardized beyond a very abstracted API (that can't even do what I want to do) so you have to implement most of it yourself and it's actually different across every system.

#### utmpx.h and Y2038
There's also the issue with the `utmpx.h` interface/the `utmpx` struct being so old that `ut_tv` has to be 32-bit even on 64-bit bi-arch systems (since they *could* run 32-bit applications where `time_t` is 32-bit). So something has to change with utmp or how login activity in general is stored anyway, or else it will encounter the Y2038 issue. And assuming that Linux wants to keep login history beyond the year 2038, something *will* change (see `lastlog2` as an example).

## Future development
I consider this project done for now. It does what I want it to do - hiding your login activity from utmpx records (that being utmp files on Linux) -  and [it's a niche use-case anyway](#why-though).