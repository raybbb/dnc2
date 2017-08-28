
// Copyright (c) 2014-2016 XDN developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <vector>
#include <ostream>
#include <istream>

#include "CryptoNoteConfig.h"
#include "crypto/hash.h"
#include "crypto/chacha.h"

namespace CryptoNote {
class AccountBase;
class ISerializer;
}

namespace CryptoNote {

class WalletUserTransactionsCache;

class WalletLegacySerializer {
public:

	WalletLegacySerializer(CryptoNote::AccountBase& account, WalletUserTransactionsCache& transactionsCache, uint8_t version=2);

#if SQ_ADD_BM2
	void serializeBM(std::ostream& stream, const std::string& password, bool saveDetailed, const std::string& cache);
#endif

  void serialize(std::ostream& stream, const std::string& password, bool saveDetailed, const std::string& cache);
  void deserialize(std::istream& stream, const std::string& password, std::string& cache);

  uint8_t m_wallet_version;
private:
  void saveKeys(CryptoNote::ISerializer& serializer);
  void loadKeys(CryptoNote::ISerializer& serializer);

  Crypto::chacha_iv encrypt(const std::string& plain, const std::string& password, std::string& cipher);
  void decrypt(const std::string& cipher, std::string& plain, Crypto::chacha_iv iv, const std::string& password);

  CryptoNote::AccountBase& account;

#if SQ_ADD_BM2
  void saveKeysBM(CryptoNote::ISerializer& serializer);
  void loadKeysBM(CryptoNote::ISerializer& serializer);
#endif

  WalletUserTransactionsCache& transactionsCache;
  const uint32_t walletSerializationVersion;
};

} //namespace CryptoNote
