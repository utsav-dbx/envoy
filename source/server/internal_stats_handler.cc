#include <iostream>
#include <map>
#include <set>
#include <string>

#include "envoy/server/internal_stats_handler.h"
#include "envoy/stats/stats.h"
#include "envoy/stats/store.h"

#include "common/stats/metric_snapshot_impl.h"

namespace Envoy {
namespace Server {



void InternalStatsHandler::snapshot(PostMergeSnapshotCb cb) {
  store_root_.mergeHistograms([this, cb] {
    cb(std::make_unique<Stats::MetricSnapshotImpl>(store_root_));
  });
}

} // namespace Server
} // namespace Envoy
