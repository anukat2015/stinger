#ifndef  STINGER_SERVER_STATE_H
#define  STINGER_SERVER_STATE_H

extern "C" {
  #include "stinger_core/stinger.h"
}

#include <pthread.h>
#include <stdint.h>

#include "stinger_stream_state.h"
#include "stinger_alg_state.h"
#include "stinger_mon_state.h"
#include "proto/stinger-batch.pb.h"
#include "proto/stinger-monitor.pb.h"

/* STL - TODO explore other options */
#include <map>
#include <string>
#include <vector>
#include <queue>

namespace gt {
  namespace stinger {

    /**
    * @brief Singleton class containing global state and configuration
    */
    class StingerServerState {

      private:

	/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ *
	 * PRIVATE PROPERTIES
	 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

	int64_t alg_lock;
	std::vector<StingerAlgState *> algs;                     
	std::vector<std::vector<StingerAlgState *> > alg_tree;
	std::map<std::string, StingerAlgState *> alg_map;        

	int64_t mon_lock;
	std::vector<StingerMonState *> monitors;                     
	std::map<std::string, StingerMonState *> monitor_map;        
	ServerToMon server_to_mon;

	int64_t dep_lock;
	std::map<std::string, std::vector<StingerAlgState *> > opt_dependencies;        
	std::map<std::string, std::vector<StingerAlgState *> > req_dependencies;        

	int64_t stream_lock;
	std::vector<StingerStreamState *> streams;
	std::map<std::string, StingerStreamState *> stream_map;

	int64_t batch_lock;
	std::queue<StingerBatch *> batches;

	int port;
	int convert_num_to_string;

	std::vector<pthread_t> threads;
	pthread_t main_loop;

	stinger_t * stinger;
	std::string stinger_loc;

	/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ *
	 * PRIVATE METHODS
	 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
	StingerServerState();

	~StingerServerState();

      public:

	/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ *
	 * PUBLIC METHODS
	 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
	static StingerServerState &
	get_server_state();

	int
	get_port();

	int
	set_port(int new_port);

	int
	convert_numbers_only_to_strings();

	int
	set_convert_numbers_only_to_strings(int new_value);

	pthread_t *
	get_main_loop() { return &main_loop; }

	void
	enqueue_batch(StingerBatch * batch);

	StingerBatch *
	dequeue_batch();

	size_t
	get_num_streams();

	StingerStreamState *
	get_stream(size_t index);

	StingerStreamState *
	get_stream(std::string & name);

	size_t
	get_num_levels();

	size_t
	get_num_algs();

	size_t
	get_num_algs(size_t level);

	StingerAlgState *
	get_alg(size_t num);

	StingerAlgState *
	get_alg(size_t level, size_t index);

	StingerAlgState *
	get_alg(const std::string & name);

        size_t
	add_alg(size_t level, StingerAlgState * alg);

	bool
	has_alg(const std::string & name);

	bool
	delete_alg(const std::string & name);

	size_t
	get_num_mons();

	StingerMonState *
	get_mon(size_t num);

	StingerMonState *
	get_mon(const std::string & name);

        size_t
	add_mon(StingerMonState * mon);

	bool
	has_mon(const std::string & name);

	void
	set_mon_stinger(std::string loc, int64_t size);

	bool
	delete_mon(const std::string & name);

	ServerToMon *
	get_server_to_mon_copy();

	pthread_t &
	push_thread(pthread_t & thread);

	void
	set_main_loop_thread(pthread_t thread);

	void
	set_stinger(stinger_t * S);

	stinger_t *
	get_stinger();

	const std::string &
	get_stinger_loc();

	void
	set_stinger_loc(const std::string & loc);
    };

  } /* gt */
} /* stinger */

#endif  /*STINGER_SERVER_STATE_H*/
