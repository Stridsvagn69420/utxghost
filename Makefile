APPNAME = utxghost
OUTDIR = build
SRCDIR = src
INSTALLDIR = /usr/local/bin

compile:
	@cmake -DCMAKE_BUILD_TYPE=Release -B$(OUTDIR) -S$(SRCDIR)
	@cmake --build $(OUTDIR) --config Release -j $(nproc)

debug:
	@cmake -DCMAKE_BUILD_TYPE=Debug -B$(OUTDIR) -S$(SRCDIR)
	@cmake --build $(OUTDIR) --config Debug -j $(nproc)

install: compile
	@install -m755 $(OUTDIR)/$(APPNAME) $(INSTALLDIR)/$(APPNAME)

uninstall:
	@rm $(INSTALLDIR)/$(APPNAME)

run: compile
	@$(OUTDIR)/$(APPNAME)

clean:
	@rm -r $(OUTDIR)