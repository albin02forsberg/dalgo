TEMPLATE = subdirs

SUBDIRS += \
    Stacks \
    Queues \
    Kalkylatoralgoritm \
    Paint \



## Jag har adderat detta!...

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
