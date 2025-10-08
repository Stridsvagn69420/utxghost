APPNAME = utxghost
OUTDIR = build
INSTALLDIR = /usr/local/bin

compile:
	@cmake -DCMAKE_BUILD_TYPE=Release -B$(OUTDIR) -S.
	@cmake --build $(OUTDIR) --config Release

install: compile
	@install -m755 $(OUTDIR)/$(APPNAME) $(INSTALLDIR)/$(APPNAME)

uninstall:
	@rm $(INSTALLDIR)/$(APPNAME)

run: compile
	@$(OUTDIR)/$(APPNAME)

clean:
	@rm -r $(OUTDIR)
