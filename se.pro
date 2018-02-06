TEMPLATE = subdirs

SUBDIRS += \
    baseapp \
    webapp \
    mobileapp \
    server

baseapp.subdir = src/base-app
webapp.subdir = src/web-app
mobileapp.subdir = src/mobile-app
server.subdir = src/server

webapp.depends = baseapp
mobileapp.depends = baseapp
