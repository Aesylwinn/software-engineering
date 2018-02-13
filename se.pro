TEMPLATE = subdirs

SUBDIRS +=      \
    baseapp     \
    webapp      \
    mobileapp   \
    server      \
    test

baseapp.subdir = src/base-app
webapp.subdir = src/web-app
mobileapp.subdir = src/mobile-app
server.subdir = src/server
test.subdir = src/test

webapp.depends = baseapp
mobileapp.depends = baseapp
test.depends = baseapp
