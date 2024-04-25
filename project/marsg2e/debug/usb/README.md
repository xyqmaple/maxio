

## 使能 Trace Event

echo 1 > /sys/kernel/debug/tracing/events/dwc2/dwc2_readl/enable
echo 1 > /sys/kernel/debug/tracing/events/dwc2/dwc2_writel/enable

cat /sys/kernel/debug/tracing/trace
