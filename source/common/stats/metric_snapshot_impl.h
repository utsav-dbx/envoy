#pragma once

#include <vector>

#include "envoy/stats/sink.h"
#include "envoy/stats/store.h"

namespace Envoy {
namespace Stats {

// Local implementation of Stats::MetricSnapshot used to flush metrics to sinks. We could
// potentially have a single class instance held in a static and have a clear() method to avoid some
// vector constructions and reservations, but I'm not sure it's worth the extra complexity until it
// shows up in perf traces.
// TODO(mattklein123): One thing we probably want to do is switch from returning vectors of metrics
//                     to a lambda based callback iteration API. This would require less vector
//                     copying and probably be a cleaner API in general.
class MetricSnapshotImpl : public MetricSnapshot {
public:
  explicit MetricSnapshotImpl(Stats::Store& store);

  // Stats::MetricSnapshot
  const std::vector<CounterSnapshot>& counters() override { return counters_; }
  const std::vector<std::reference_wrapper<const Stats::Gauge>>& gauges() override {
    return gauges_;
  };
  const std::vector<std::reference_wrapper<const Stats::ParentHistogram>>& histograms() override {
    return histograms_;
  }
  const std::vector<std::reference_wrapper<const Stats::TextReadout>>& textReadouts() override {
    return text_readouts_;
  }

private:
  std::vector<Stats::CounterSharedPtr> snapped_counters_;
  std::vector<CounterSnapshot> counters_;
  std::vector<Stats::GaugeSharedPtr> snapped_gauges_;
  std::vector<std::reference_wrapper<const Stats::Gauge>> gauges_;
  std::vector<Stats::ParentHistogramSharedPtr> snapped_histograms_;
  std::vector<std::reference_wrapper<const Stats::ParentHistogram>> histograms_;
  std::vector<Stats::TextReadoutSharedPtr> snapped_text_readouts_;
  std::vector<std::reference_wrapper<const Stats::TextReadout>> text_readouts_;
};

}
}