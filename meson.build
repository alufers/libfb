project('fblib', ['c'])
FACEBOOKSOURCES = [
	'api.c',
	'api.h',
	'http.c',
	'http.h',
	'id.h',
	'internal.h',
	'main.c',
	'marshal.c',
	'marshal.h',
	'json.c',
	'json.h',
	'mqtt.c',
	'mqtt.h',
	'thrift.c',
	'thrift.h',
	'util.c',
	'util.h'
]

json = dependency('json-glib-1.0')
glib = dependency('glib-2.0')
gio = dependency('gio-2.0')
libsoup = dependency('libsoup-2.4')
    
executable('sample', 'main.c', dependencies : [json, libsoup, glib, gio], sources: FACEBOOKSOURCES)



