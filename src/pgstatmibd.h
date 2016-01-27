/**
 * pgstatmibd.h
 */

#ifndef PGSTATMIBD_H
#define PGSTATMIBD_H

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

/*
 * Local includes from PostgreSQL libpq
 */
#include "postgres_fe.h"
#include "libpq-fe.h"

/*
 * Global includes from Net-SNMP
 */
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <net-snmp/agent/mib_modules.h>
#include <net-snmp/agent/util_funcs.h>

//extern 
PGconn *dbconn;

RETSIGTYPE
stop_server(int);

#endif

