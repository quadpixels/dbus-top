dbus-top is a top-like tool for DBus. It was originally designed for OpenBMC due to its extensive usage
of the DBus protocol, but can also run on a regular Linux system.

```
*******************************************************************************************************
*Message Type          | msg/s |Method Call Time (us) Histogram|History     (Total msg/s)             *
*Method Call             70.33 |   159-.:   ::.                |-                          -200       *
*Method Return           69.84 |    44-::. .:::::.             |-                          -150       *
*Signal                   1.00 |    12-::::::::::::::          |-               :.: .:    :-100       *
*Error                    0.00 |     3-::::::::::::::..: :.::: |-               ::::::    :-50        *
*Total                  141.17 |1%-99% 439.00         28264.00 |-              .::::::....:-0         *
*******************************************************************************************************
| Columns 1-2 of 1                  14 sensors    | Msg/s   Destination         Sender                |
|   p3v_bat_adc                                   | 0.50    (null)              org.freedesktop.DBus  |
|   fan4                                          | 50.38   :1.139              :1.0                  |
|   pcie_fan0                                     | 10.97   :1.139              :1.75                 |
|   pcie_fan2                                     | 5.99    :1.139              :1.83                 |
|   fan5                                          | 0.50    :1.139              :1.87                 |
|   fan1                                          | 2.49    :1.139              org.freedesktop.DBus  |
|   fan2                                          | 0.50    org.freedesktop.... :1.139                |
|   fan0                                          | 2.00    org.freedesktop.... :1.139                |
|   fan3                                          | 10.97   org.freedesktop.... :1.139                |
|   pcie_fan3                                     | 5.99    org.freedesktop.... :1.139                |
|   pcie_fan1                                     | 50.88   org.freedesktop.... :1.139                |
|   fan6                                          |                                                   |
|   cpu1temp                                      |                                                   |
|   cpu0temp                                      |                                                   |
|                                                 |                                                   |
+-------------------------------------------------+---------------------------------------------------+
```
