
// Copyright (c) 2014-2017 darknetspace developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <cstdint>
#include <initializer_list>

//#ifndef  SQ_TEST
//#define SQ_TEST 1
//#endif

//#ifndef SQ_UI_TEST
//#define SQ_UI_TEST 0
//#endif

//#ifndef SQ_GENESIS_TEST
//#define SQ_GENESIS_TEST 1
//#endif
//
////  change time (utc) to local
//#ifndef SQ_TEST_WALLET_TIME
//#define SQ_TEST_WALLET_TIME 1
//#endif

#ifndef SQ_ADD_PEER_FRAME
#define SQ_ADD_PEER_FRAME 1
#endif

#ifndef SQ_ADD_DONATION
#define SQ_ADD_DONATION 1
#endif

#ifndef SQ_ADD_BM
#define SQ_ADD_BM 1
#define SQ_ADD_BM2 1
#define SQ_ADD_BM_WALLET 1
#define SQ_ADD_BM_WALLETUI 1
#define SQ_ADD_BM_SEGMENT  1
#define SQ_CHANGE_GROUP_PARM  1
#include <string>
#endif

#ifndef SQ_REMOVE_MAXIN
#define SQ_REMOVE_MAXIN 1
#endif

#ifndef SQ_ADD_ALIAS
#define SQ_ADD_ALIAS 1
#ifndef CHECK_AND_ASSERT_MES
#define CHECK_AND_ASSERT_MES(expr, fail_ret_val, message)   do{if(!(expr)) {fail_msg_writer()<<message; return fail_ret_val;};}while(0)
#endif
#endif

#if SQ_ADD_ALIAS
#define SQ_BINARY_DEBUG 0
#else
#define SQ_BINARY_DEBUG 1
#endif

namespace CryptoNote {
namespace parameters {

const uint64_t CRYPTONOTE_MAX_BLOCK_NUMBER                   = 500000000;
const size_t   CRYPTONOTE_MAX_BLOCK_BLOB_SIZE                = 500000000;
const size_t   CRYPTONOTE_MAX_TX_SIZE                        = 1000000000;
const uint64_t CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX       = 'H'; // addresses start with "D"
const size_t   CRYPTONOTE_MINED_MONEY_UNLOCK_WINDOW          = 30;
const uint64_t CRYPTONOTE_BLOCK_FUTURE_TIME_LIMIT            = 60 * 60 * 2;

const size_t   BLOCKCHAIN_TIMESTAMP_CHECK_WINDOW             = 30;

const uint64_t MONEY_SUPPLY                                  = UINT64_C(500000000000000000);

const size_t   CRYPTONOTE_REWARD_BLOCKS_WINDOW               = 100;
const size_t   CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE     = 32000; //size of block (bytes) after which reward for block calculated using block size
const size_t   CRYPTONOTE_COINBASE_BLOB_RESERVED_SIZE        = 600;
const size_t   CRYPTONOTE_DISPLAY_DECIMAL_POINT              = 8;
// COIN - number of smallest units in one coin
const uint64_t COIN                                          = UINT64_C(100000000);  // pow(10, 8)
const uint64_t MINIMUM_FEE                                   = UINT64_C(100000);     // pow(10, 5)
const uint64_t DEFAULT_DUST_THRESHOLD                        = UINT64_C(100000);     // pow(10, 5)

const uint64_t DIFFICULTY_TARGET                             = 240; // seconds
const uint64_t EXPECTED_NUMBER_OF_BLOCKS_PER_DAY             = 24 * 60 * 60 / DIFFICULTY_TARGET;
const size_t   DIFFICULTY_WINDOW                             = 240; // blocks
const size_t   DIFFICULTY_CUT                                = 30;  // timestamps to cut after sorting
const size_t   DIFFICULTY_LAG                                = 15;
static_assert(2 * DIFFICULTY_CUT <= DIFFICULTY_WINDOW - 2, "Bad DIFFICULTY_WINDOW or DIFFICULTY_CUT");

const uint64_t DEPOSIT_MIN_AMOUNT                            = 150 * COIN;
const uint32_t DEPOSIT_MIN_TERM                              = 11000;
const uint32_t DEPOSIT_MAX_TERM                              = 12 * 11000;
const uint64_t DEPOSIT_MIN_TOTAL_RATE_FACTOR                 = 77000;
const uint64_t DEPOSIT_MAX_TOTAL_RATE                        = 11;
static_assert(DEPOSIT_MIN_TERM > 0, "Bad DEPOSIT_MIN_TERM");
static_assert(DEPOSIT_MIN_TERM <= DEPOSIT_MAX_TERM, "Bad DEPOSIT_MAX_TERM");
static_assert(DEPOSIT_MIN_TERM * DEPOSIT_MAX_TOTAL_RATE > DEPOSIT_MIN_TOTAL_RATE_FACTOR, "Bad DEPOSIT_MIN_TOTAL_RATE_FACTOR or DEPOSIT_MAX_TOTAL_RATE");

const size_t   MAX_BLOCK_SIZE_INITIAL                        = CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE * 10;
const uint64_t MAX_BLOCK_SIZE_GROWTH_SPEED_NUMERATOR         = 100 * 1024;
const uint64_t MAX_BLOCK_SIZE_GROWTH_SPEED_DENOMINATOR       = 365 * 24 * 60 * 60 / DIFFICULTY_TARGET;

const uint64_t CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_BLOCKS     = 1;
const uint64_t CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_SECONDS    = DIFFICULTY_TARGET * CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_BLOCKS;

const uint64_t CRYPTONOTE_MEMPOOL_TX_LIVETIME                = (60 * 60 * 14); //seconds, 14 hours
const uint64_t CRYPTONOTE_MEMPOOL_TX_FROM_ALT_BLOCK_LIVETIME = (60 * 60 * 24); //seconds, one day
const uint64_t CRYPTONOTE_NUMBER_OF_PERIODS_TO_FORGET_TX_DELETED_FROM_POOL = 7;  // CRYPTONOTE_NUMBER_OF_PERIODS_TO_FORGET_TX_DELETED_FROM_POOL * CRYPTONOTE_MEMPOOL_TX_LIVETIME = time to forget tx

const size_t   FUSION_TX_MAX_SIZE                            = CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE * 30 / 100;
const size_t   FUSION_TX_MIN_INPUT_COUNT                     = 12;
const size_t   FUSION_TX_MIN_IN_OUT_COUNT_RATIO              = 4;

const uint64_t UPGRADE_HEIGHT                                = 0;
const unsigned UPGRADE_VOTING_THRESHOLD                      = 90;               // percent
const size_t   UPGRADE_VOTING_WINDOW                         = EXPECTED_NUMBER_OF_BLOCKS_PER_DAY;  // blocks
const size_t   UPGRADE_WINDOW                                = EXPECTED_NUMBER_OF_BLOCKS_PER_DAY;  // blocks
static_assert(0 < UPGRADE_VOTING_THRESHOLD && UPGRADE_VOTING_THRESHOLD <= 100, "Bad UPGRADE_VOTING_THRESHOLD");
static_assert(UPGRADE_VOTING_WINDOW > 1, "Bad UPGRADE_VOTING_WINDOW");

const char     CRYPTONOTE_BLOCKS_FILENAME[]                  = "blocks.dat";
const char     CRYPTONOTE_BLOCKINDEXES_FILENAME[]            = "blockindexes.dat";
const char     CRYPTONOTE_BLOCKSCACHE_FILENAME[]             = "blockscache.dat";
const char     CRYPTONOTE_POOLDATA_FILENAME[]                = "poolstate.bin";
const char     P2P_NET_DATA_FILENAME[]                       = "p2pstate.bin";
const char     CRYPTONOTE_BLOCKCHAIN_INDICES_FILENAME[]      = "blockchainindices.dat";
const char     MINER_CONFIG_FILE_NAME[]                      = "miner_conf.json";
} // parameters

#if SQ_GENESIS_TEST
const uint64_t BLOCK_REWARD_GENESIS = (UINT64_C(1) * parameters::COIN);

const uint64_t BLOCK_REWARD_FIRST = (UINT64_C(1844000000) * parameters::COIN);
#else

const uint64_t BLOCK_REWARD_GENESIS = (UINT64_C(1) * parameters::COIN);

const uint64_t BLOCK_REWARD_FIRST = (UINT64_C(1844000000) * parameters::COIN);

#endif
const uint64_t START_BLOCK_REWARD                            = (UINT64_C(200) * parameters::COIN);
const uint64_t MIN_BLOCK_REWARD = (UINT64_C(200) * parameters::COIN);
const uint64_t BLOCK_REWARD_LOSS = (UINT64_C(0) * parameters::COIN);
const uint64_t REWARD_CHANGING_INTERVAL = (UINT64_C(11000));

#if SQ_TEST
const char     CRYPTONOTE_NAME[] = "darknetcoin_testsq";
#else
const char     CRYPTONOTE_NAME[] = "darknetcoin";
#endif

#if SQ_GENESIS_TEST
const char     GENESIS_COINBASE_TX_HEX[] = "011e01ff000180c2d72f02a7b8bb167713d0340379c5343e564b0ddcb34648c01e86acd9b95cf11e24166f2101195aad403b27f4046782be7cf5ccf2ae429a00e97ceff5c46fb78100f5a8d04e";
#else
const char     GENESIS_COINBASE_TX_HEX[] = "011e01ff000180c2d72f02115d19dba13192544710840713a7c9507d7ed18c1a50c4b05759feb0660d099e2101701b8c4fbd8a08f9d4650a1667b9208ae10a2da2afa3084d48fdb6cd5086452b";
#endif

const uint32_t GENESIS_NONCE                                 = 420;

const uint8_t  TRANSACTION_VERSION_1                         =  1;
const uint8_t  TRANSACTION_VERSION_2                         =  2;
const uint8_t  BLOCK_MAJOR_VERSION_1                         =  1;
const uint8_t  BLOCK_MAJOR_VERSION_2                         =  2;
const uint8_t  BLOCK_MINOR_VERSION_0                         =  0;
const uint8_t  BLOCK_MINOR_VERSION_1                         =  1;

const size_t   BLOCKS_IDS_SYNCHRONIZING_DEFAULT_COUNT        =  10000;  //by default, blocks ids count in synchronizing
const size_t   BLOCKS_SYNCHRONIZING_DEFAULT_COUNT            =  200;    //by default, blocks count in blocks downloading
const size_t   COMMAND_RPC_GET_BLOCKS_FAST_MAX_COUNT         =  1000;

#if SQ_TEST
const int      P2P_DEFAULT_PORT = 12080;
const int      RPC_DEFAULT_PORT = 12081;
#else
const int      P2P_DEFAULT_PORT = 38908;
const int      RPC_DEFAULT_PORT = 57709;
#endif

const size_t   P2P_LOCAL_WHITE_PEERLIST_LIMIT                =  1000;
const size_t   P2P_LOCAL_GRAY_PEERLIST_LIMIT                 =  5000;

const size_t   P2P_CONNECTION_MAX_WRITE_BUFFER_SIZE          = 16 * 1024 * 1024; // 16 MB
const uint32_t P2P_DEFAULT_CONNECTIONS_COUNT                 = 8;
const size_t   P2P_DEFAULT_WHITELIST_CONNECTIONS_PERCENT     = 70;
const uint32_t P2P_DEFAULT_HANDSHAKE_INTERVAL                = 60;            // seconds
const uint32_t P2P_DEFAULT_PACKET_MAX_SIZE                   = 50000000;      // 50000000 bytes maximum packet size
const uint32_t P2P_DEFAULT_PEERS_IN_HANDSHAKE                = 250;
const uint32_t P2P_DEFAULT_CONNECTION_TIMEOUT                = 5000;          // 5 seconds
const uint32_t P2P_DEFAULT_PING_CONNECTION_TIMEOUT           = 2000;          // 2 seconds
const uint64_t P2P_DEFAULT_INVOKE_TIMEOUT                    = 60 * 2 * 1000; // 2 minutes
const size_t   P2P_DEFAULT_HANDSHAKE_INVOKE_TIMEOUT          = 5000;          // 5 seconds
const char     P2P_STAT_TRUSTED_PUB_KEY[]                    = "44165823f0e1257378eb045f9ba9e0beab580cfd3c35bc2b1dd1b5054eca46d4";

#if SQ_ADD_BM
const std::string strMSG = "Replay-To:";
const uint64_t BMESSAGE_FEE = UINT64_C(100000000);
const int SEGMENT_SIZE = 50;
#define BM_GROUP_NUM 6
#define WALLET_VERSION_BM 3
#define ACCOUNT_OWN_ID 0
#define BM_ID_MAX 255
#endif

#define CURRENCY_BLOCK_GRANTED_FULL_REWARD_ZONE_ENLARGE_STARTING_BLOCK     147000
#define CURRENCY_DONATIONS_ADDRESS							"D9gRL2qmzRhDBx6bZywXy4ACSy6ioGm355RsS8woieKUZnez8sTGxAU3zJ18tPHbdpaF627ah6XmJ848JriXgthC1TQU8SK"
#define CURRENCY_DONATIONS_ADDRESS_TRACKING_KEY				 "be4d07be0bd80a9d9d4d9a46e7e06d2f15eb38d8e457a284ca908eb7f9dbd104"
#define MAKE_ALIAS_MINIMUM_FEE                          ((uint64_t)100 * parameters::COIN) //100DNC

#define SPEND_AGE 3

const std::initializer_list<const char*> SEED_NODES = {
#if SQ_TEST
	"139.196.154.108:12080",
	"121.40.148.89:12080",
	"182.92.201.174:12080",
	"106.187.55.89:12080",
	"115.29.52.162:12080",
	"101.200.143.5:12080",
	"121.40.48.33:12080",
	"120.24.15.70:12080"
#else
	"139.196.154.108:38908",
	"121.40.148.89:38908",
	"182.92.201.174:38908",
	"106.187.55.89:38908",
	"115.29.52.162:38908",
	"101.200.143.5:38908",
	"121.40.48.33:38908",
	"120.24.15.70:38908"
#endif
};

struct CheckpointData {
  uint32_t height;
  const char* blockId;
};

#ifdef __GNUC__
__attribute__((unused))
#endif

// You may add here other checkpoints using the following format:
// {<block height>, "<block hash>"},
const std::initializer_list<CheckpointData> CHECKPOINTS = {
 
};

} // CryptoNote

#define ALLOW_DEBUG_COMMANDS
