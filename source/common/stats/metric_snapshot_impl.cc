#include "common/stats/metric_snapshot_impl.h"

namespace Envoy {
namespace Stats {

MetricSnapshotImpl::MetricSnapshotImpl(Stats::Store& store) {
  snapped_counters_ = store.counters();
  counters_.reserve(snapped_counters_.size());
  for (const auto& counter : snapped_counters_) {
    counters_.push_back({counter->latch(), *counter});
  }

  snapped_gauges_ = store.gauges();
  gauges_.reserve(snapped_gauges_.size());
  for (const auto& gauge : snapped_gauges_) {
    ASSERT(gauge->importMode() != Stats::Gauge::ImportMode::Uninitialized);
    gauges_.push_back(*gauge);
  }

  snapped_histograms_ = store.histograms();
  histograms_.reserve(snapped_histograms_.size());
  for (const auto& histogram : snapped_histograms_) {
    histograms_.push_back(*histogram);
  }

  snapped_text_readouts_ = store.textReadouts();
  text_readouts_.reserve(snapped_text_readouts_.size());
  for (const auto& text_readout : snapped_text_readouts_) {
    text_readouts_.push_back(*text_readout);
  }
}

}
}