/**
 * pgstatBgWriter MIB group interface
 *
 * Note: this file originally auto-generated by mib2c
 */
#ifndef PGSTATBGWRITER_H
#define PGSTATBGWRITER_H

/* module name */
#define PGSTATBGWRITER_NAME	"pgstatBgWriter"

#define PGSTATBGWRITER_CACHE_TIMEOUT	30	// in seconds

/* structures */
typedef struct {
	u_long checkpoints_timed;
	u_long checkpoints_req;
	u_long buffers_checkpoint;
	u_long buffers_clean;
	u_long maxwritten_clean;
	u_long buffers_backend;
	u_long buffers_alloc;
	time_t last_load; // for caching control
} pgstatBgWriterData;

/* function declarations */
void 			init_pgstatBgWriter(void);
void 			refresh_numbers_pgstatBgWriter(void);
void 			load_numbers_from_db_pgstatBgWriter(void);
FindVarMethod	getvalue_pgstatBgWriter;

/* scalar number definitions */
#define PGSTATBGWRITER_CHECKPOINTSTIMED			1
#define PGSTATBGWRITER_CHECKPOINTSREQUESTED		2
#define PGSTATBGWRITER_BUFFERSCHECKPOINT		3
#define PGSTATBGWRITER_BUFFERSCLEAN				4
#define PGSTATBGWRITER_MAXWRITTENCLEAN			5
#define PGSTATBGWRITER_BUFFERSBACKEND			6
#define PGSTATBGWRITER_BUFFERSALLOCATED			7

#define PGSTATBGWRITER_FIRST		PGSTATBGWRITER_CHECKPOINTSTIMED
#define PGSTATBGWRITER_LAST		PGSTATBGWRITER_BUFFERSALLOCATED

#endif /* PGSTATBGWRITER_H */
