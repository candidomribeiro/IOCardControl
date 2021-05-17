***********************
* To start the daemon *
***********************

Go to the daqnavi_daemon folder,

[Your Path]/advantech/daqnavi_daemon

Execute the file: daqnavi_daemon.d with root permission

Usage: daqnavi_daemon.d {start|stop|restart|status}

To start the daemon use: ./daqnavi_daemon.d start

If the daemon starts successfully the `daqnavi` devices are ready to use.


************************************
* To install the IOCardControl lib *
************************************

Go to IOCardControl folder and execute with root permission the following command line:

make install


***************************
* Using the installed lib *
***************************

You must type on the compiler command line the options -lbiodaq and -lIOCardControl
If you use QtCreator just add these refences at LIBS variable in your .pro file, for example:

LIBS += -lbiodaq \
        -lIOCardControl

