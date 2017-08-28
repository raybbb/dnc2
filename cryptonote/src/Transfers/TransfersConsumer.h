
// Copyright (c) 2014-2016 XDN developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include "IBlockchainSynchronizer.h"
#include "ITransfersSynchronizer.h"
#include "TransfersSubscription.h"
#include "TypeHelpers.h"

#include "crypto/crypto.h"

#include "IObservableImpl.h"

#include <unordered_set>

#if SQ_ADD_BM2
#include "CommonTypes.h"
#include "CryptoTypes.h"
#endif

namespace CryptoNote {

class INode;

class TransfersConsumer: public IObservableImpl<IBlockchainConsumerObserver, IBlockchainConsumer> {
public:

	TransfersConsumer(const CryptoNote::Currency& currency, INode& node, const Crypto::SecretKey& viewSecret);
#if SQ_ADD_BM2
	bool addViewScret(Crypto::SecretKeyBM& viewSecret);
	bool deleteViewScret(const int& _id);
#endif

  ITransfersSubscription& addSubscription(const AccountSubscription& subscription);
  // returns true if no subscribers left
  bool removeSubscription(const AccountPublicAddress& address);
  ITransfersSubscription* getSubscription(const AccountPublicAddress& acc);
  void getSubscriptions(std::vector<AccountPublicAddress>& subscriptions);

  void initTransactionPool(const std::unordered_set<Crypto::Hash>& uncommitedTransactions);
  
  // IBlockchainConsumer
  virtual SynchronizationStart getSyncStart() override;
  virtual void onBlockchainDetach(uint32_t height) override;
  virtual bool onNewBlocks(const CompleteBlock* blocks, uint32_t startHeight, uint32_t count) override;
  virtual std::error_code onPoolUpdated(const std::vector<std::unique_ptr<ITransactionReader>>& addedTransactions, const std::vector<Crypto::Hash>& deletedTransactions) override;
  virtual const std::unordered_set<Crypto::Hash>& getKnownPoolTxIds() const override;

  virtual std::error_code addUnconfirmedTransaction(const ITransactionReader& transaction) override;
  virtual void removeUnconfirmedTransaction(const Crypto::Hash& transactionHash) override;

private:

  template <typename F>
  void forEachSubscription(F action) {
    for (const auto& kv : m_subscriptions) {
      action(*kv.second);
    }
  }

  struct PreprocessInfo {
    std::unordered_map<Crypto::PublicKey, std::vector<TransactionOutputInformationIn>> outputs;
    std::vector<uint32_t> globalIdxs;

#if SQ_ADD_BM2
	uint8_t m_id;
#endif
  };

  std::error_code preprocessOutputs(const TransactionBlockInfo& blockInfo, const ITransactionReader& tx, PreprocessInfo& info);
  std::error_code processTransaction(const TransactionBlockInfo& blockInfo, const ITransactionReader& tx);
  void processTransaction(const TransactionBlockInfo& blockInfo, const ITransactionReader& tx, const PreprocessInfo& info);
  void processOutputs(const TransactionBlockInfo& blockInfo, TransfersSubscription& sub, const ITransactionReader& tx,
    const std::vector<TransactionOutputInformationIn>& outputs, const std::vector<uint32_t>& globalIdxs, bool& contains, bool& updated);

  std::error_code getGlobalIndices(const Crypto::Hash& transactionHash, std::vector<uint32_t>& outsGlobalIndices);

  void updateSyncStart();

  SynchronizationStart m_syncStart;
  const Crypto::SecretKey m_viewSecret;
  // map { spend public key -> subscription }
  std::unordered_map<Crypto::PublicKey, std::unique_ptr<TransfersSubscription>> m_subscriptions;
  std::unordered_set<Crypto::PublicKey> m_spendKeys;
  std::unordered_set<Crypto::Hash> m_poolTxs;

  INode& m_node;
  const CryptoNote::Currency& m_currency;

#if SQ_ADD_BM2
  std::vector<Crypto::SecretKeyBM> m_viewSecretBM;
  void processOutputs(const TransactionBlockInfo& blockInfo, TransfersSubscription& sub, const ITransactionReader& tx,
	  const std::vector<TransactionOutputInformationIn>& transfers, const std::vector<uint32_t>& globalIdxs, bool& contains, bool& updated, uint8_t m_id);
#endif
};

}
