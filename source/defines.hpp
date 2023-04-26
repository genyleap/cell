/*!
 * Gen3 License
 *
 * @file        defines.hpp
 * @brief       This file is part of the Cell engine.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     libCell
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 */

#ifndef CELL_DEFINES_HPP
#define CELL_DEFINES_HPP

namespace Cell::Defines {

#define OK          0x1
#define ON          0x1
#define CANCEL      0x0
#define FAILED      0x0
#define SUCCESS     0x0
#define OFF         0x0

#define CELL_ABSTRACTS 0x1 // Abstraction

#define MESSAGE_OK      "OK"
#define MESSAGE_FAILED  "FAILED"
#define MESSAGE_YES     "YES"
#define MESSAGE_NO      "NO"
#define MESSAGE_ERROR   "ERROR"

#define ENGINE_DEFAULT      "Pure Cell"
#define ENGINE_BOOST        "Boost"

#define ERROR_NULL          10001
#define ERROR_HANDLER       10002
#define ERROR_SUBTRACK      10003
#define ERROR_REFRENCE      10004
#define ERROR_DLL           10005
#define ERROR_NETWORK       65102  // Message for Network Error.
#define ERROR_WINDOWS       12111
#define ERROR_SAVED         64511
#define ERROR_DB_CONNECT    64001
#define ERROR_LOADING       64522

//! Core defines.
#undef  CELL_KERNEL
#define CELL_KERNEL 0x1
#undef  CELL_BACKEND
#define CELL_BACKEND 0x1
#undef  CELL_VIEW
#define CELL_VIEW 0x1
#undef  CELL_TEMPLATES
#define CELL_TEMPLATES 0x1

#undef  CELL_MODULE
#define CELL_MODULE 0x1

#undef  CELL_PLUGIN
#define CELL_PLUGIN 0x1

/*---------------------Default ports------------------------*/
// Port numbers range from 0 to 65536, but only port numbers 0 to 1024 are
// reserved for privileged services and designated as well-known ports. This list
// of well-known port numbers specifies the port used by the server process as
// its contact port.

#define CELL_PORT_TCP           1             // TCP Port Service Multiplexer (TCPMUX)
#define CELL_PORT_RJE           5             // Remote Job Entry (RJE)
#define CELL_PORT_ECHO          7             // ECHO
#define CELL_PORT_MSP           18            // Message Send Protocol (MSP)
#define CELL_PORT_FTP           20            // FTP -- Data
#define CELL_PORT_FTP_CONTROL   21            // FTP Control
#define CELL_PORT_SSH           22            // SSH Remote Login Protocol
#define CELL_PORT_TELNET        23            // Telnet
#define CELL_PORT_SMTP          25            // Simple Mail Transfer Protocol (SMTP)
#define CELL_PORT_MGS_ICP       29            // MSG ICP
#define CELL_PORT_TIME_P        37            // Time
#define CELL_PORT_HNS           42            // Host Name Server (Nameserv)
#define CELL_PORT_WHOIS         43            // WhoIs
#define CELL_PORT_LHP           49            // Login Host Protocol (Login)
#define CELL_PORT_DNS           53            // Domain Name System (DNS)
#define CELL_PORT_TFTP          69            // Trivial File Transfer Protocol (TFTP)
#define CELL_PORT_GOPHER        70            // Gopher Services
#define CELL_PORT_FINGER        79            // Finger
#define CELL_PORT_APACHE        80            // Apache HTTP Server
#define CELL_PORT_HTTP          80            // HTTP
#define CELL_PORT_X400          103           // X.400 Standard
#define CELL_PORT_SNA           108           // SNA Gateway Access Server
#define CELL_PORT_POP2          109           // POP2
#define CELL_PORT_POP3          110           // POP3
#define CELL_PORT_SFTP          115           // Simple File Transfer Protocol (SFTP)
#define CELL_PORT_SQL_SERVICES  118           // SQL Services
#define CELL_PORT_NNTP          119           // Newsgroup (NNTP)
#define CELL_PORT_NET_BIOS      137           // NetBIOS Name Service
#define CELL_PORT_NET_BIOS_DS   139           // NetBIOS Datagram Service
#define CELL_PORT_IMAP          143           // Interim Mail Access Protocol (IMAP)
#define CELL_PORT_NET_BIOS_SS   150           // NetBIOS Session Service
#define CELL_PORT_SNMP          161           // SNMP
#define CELL_PORT_BGP           179           // Border Gateway Protocol (BGP)
#define CELL_PORT_GACP          190           // Gateway Access Control Protocol (GACP)
#define CELL_PORT_IRC           194           // Internet Relay Chat (IRC)
#define CELL_PORT_DLS           197           // Directory Location Service (DLS)
#define CELL_PORT_DLAP          389           // Lightweight Directory Access Protocol (LDAP)
#define CELL_PORT_NOVELL_IP     396           // Novell Netware over IP
#define CELL_PORT_HHTPS         443           // HTTPS
#define CELL_PORT_SNPP          444           // Simple Network Paging Protocol (SNPP)
#define CELL_PORT_MICORSOFT_DS  445           // Microsoft-DS
#define CELL_PORT_APPLE_Q_TIME  458           // Apple QuickTime
#define CELL_PORT_DHCP_CLIENT   546           // DHCP Client
#define CELL_PORT_DHCP_SERVER   547           // DHCP Server
#define CELL_PORT_SNEWS         563           // SNEWS
#define CELL_PORT_MSN           569           // MSN
#define CELL_PORT_VPP           4643          // Virtuosso Power Panel
#define CELL_PORT_SOCKS         1080          // Socks

//!Database drivers
#define CELL_PORT_MYSQL_DB      3306          // MySQL Database Server
#define CELL_PORT_POSTGRESQL_DB 5432          // PostgreSQL Database Server
#define CELL_PORT_SQL_SERVER_DB 156           // SQL Server

//!Server addresses
#define CELL_GENYLEAP_URL                   "http://genyleap.com"
#define CELL_GENYLEAP_SSL_URL               "https://genyleap.com"

#define CELL_MICROSOFT_URL                  "http://microsoft.com"
#define CELL_MICROSOFT_SSL_URL              "https://microsoft.com"

#define CELL_APPLE_NS_USA                   "104.154.51.7"
#define CELL_APPLE_NS_EUROPE                "104.155.28.90"
#define CELL_APPLE_NS_ASIA                  "104.155.220.58"
#define CELL_APPLE_NS_SOUTH_AMERICA         "35.199.88.219"
#define CELL_APPLE_NS_AUSTRALIA_OCEANIA     "35.189.47.23"

#define CELL_APPLE_URL                      "http://apple.com"
#define CELL_APPLE_SSL_URL                  "https://apple.com"
#define CELL_APPLE_NS_USA                   "104.154.51.7"
#define CELL_APPLE_NS_EUROPE                "104.155.28.90"
#define CELL_APPLE_NS_ASIA                  "104.155.220.58"
#define CELL_APPLE_NS_SOUTH_AMERICA         "35.199.88.219"
#define CELL_APPLE_NS_AUSTRALIA_OCEANIA     "35.189.47.23"

#define CELL_CLOUD_FLARE_NS1                "1.1.1.1"
#define CELL_CLOUD_FLARE_NS2                "1.0.0.1"

#define CELL_QUAD9_NS1                      "9.9.9.9"
#define CELL_QUAD9_NS2                      "149.112.112.112"

#define CELL_GOOGLE_URL                     "http://google.com"
#define CELL_GOOGLE_SSL_URL                 "https://google.com"
#define CELL_GOOGLE_NS1                     "8.8.8.8"
#define CELL_GOOGLE_NS2                     "8.8.4.4"

//! Protocols
#define CELL_PROTOCOL_HTTPS   "https://"      // SECURED PROTOCOL (USING SSL , 443-PORT)
#define CELL_PROTOCOL_HTTP    "http://"       // UNSECURTED PROTOCOL (USING PORT : 80)
#define CELL_PROTOCOL_FTP     "ftp://"        // FTP PTOTOCOL - FTP data transfer (USING PORT : 20)

#define CELL_BATTERY_ENERGY 10

//! System actions
#define CELL_EXIT 0;

}

#endif // CELL_DEFINES_HPP
