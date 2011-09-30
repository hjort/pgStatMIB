/*
 * Note: this file originally auto-generated by mib2c
 */
#ifndef PGSTATDATABASETABLE_H
#define PGSTATDATABASETABLE_H

//config_require(host/data_access/swinst)

/*
 * function declarations 
 */
void init_pgstatDatabaseTable(void);
void initialize_table_pgstatDatabaseTable(void);
Netsnmp_Node_Handler pgstatDatabaseTable_handler;

/*
 * column number definitions for table pgstatDatabaseTable 
 */
#define COLUMN_PGSTATDATABASEID		1
#define COLUMN_PGSTATDATABASENAME		2
#define COLUMN_PGSTATDATABASEBACKENDS		3
#define COLUMN_PGSTATDATABASECOMMITS		4
#define COLUMN_PGSTATDATABASEROLLBACKS		5
#define COLUMN_PGSTATDATABASEBLOCKSREAD		6
#define COLUMN_PGSTATDATABASEBLOCKSHIT		7
#define COLUMN_PGSTATDATABASETUPLESRETURNED		8
#define COLUMN_PGSTATDATABASETUPLESFETCHED		9
#define COLUMN_PGSTATDATABASETUPLESINSERTED		10
#define COLUMN_PGSTATDATABASETUPLESUPDATED		11
#define COLUMN_PGSTATDATABASETUPLESDELETED		12
#define COLUMN_PGSTATDATABASESIZEMB		13
#define COLUMN_PGSTATDATABASEROLLBACKRATIO		14
#define COLUMN_PGSTATDATABASECACHEHITRATIO		15
#define COLUMN_PGSTATDATABASETUPLESMODIFIED		16

#endif	/* PGSTATDATABASETABLE_H */
