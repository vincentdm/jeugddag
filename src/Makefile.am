SUBDIRS=logger csvfile libjeugddag
bin_PROGRAMS=jeugddagcli

INCLUDES=\
	-I$(top_srcdir)/src/csvfile \
	-I$(top_srcdir)/src/libjeugddag

jeugddagcli_SOURCES=\
		jeugddag-cli.cpp
	
jeugddagcli_LDADD=\
	$(top_builddir)/src/logger/liblogger.la \
	$(top_builddir)/src/libjeugddag/libjeugddag.la \
	$(top_builddir)/src/csvfile/libcsvfile.la

