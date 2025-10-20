declare module "@plotx" {

    import {BlockPos} from "@minecraft";

    export class PlotCross extends PlotAABB implements InstanceClassHelper<PlotCross> {
        constructor();

        constructor(x: number, z: number);

        constructor(pos: BlockPos);

        toString(): string;

        isValid(): boolean;
    }
}