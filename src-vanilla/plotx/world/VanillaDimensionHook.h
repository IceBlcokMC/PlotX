#pragma once


namespace plotx {


class VanillaDimensionHook {
public:
    VanillaDimensionHook() = delete;

    enum TargetDimension { Overworld = 0, Nether = 1, TheEnd = 2 };

    static bool isHooked();

    static TargetDimension getTarget();

    static void hook(TargetDimension target);

    static void unhook();
};


} // namespace plotx