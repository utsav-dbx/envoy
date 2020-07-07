#pragma once

#include "envoy/stats/sink.h"
#include "envoy/stats/stats.h"
#include "envoy/stats/store.h"

namespace Envoy {
namespace Server {

using PostMergeSnapshotCb = std::function<void(Envoy::Stats::MetricSnapshotPtr)>;

class InternalStatsHandler {

public:
  explicit InternalStatsHandler(Stats::StoreRoot& root) : store_root_(root) {}

  // Merges histograms and calls PostMergeSnapshotCb with a snapshot
  void snapshot(PostMergeSnapshotCb);

private:
  Stats::StoreRoot& store_root_;
};

using InternalStatsHandlerPtr = std::unique_ptr<InternalStatsHandler>;

} // namespace Server
} // namespace Envoy