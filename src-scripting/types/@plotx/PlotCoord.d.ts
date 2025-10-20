import {BlockPos} from "@minecraft";

declare module "@plotx" {

    export class PlotCoord extends PlotAABB implements InstanceClassHelper<PlotCoord> {
        constructor(x: number, z: number);

        constructor(pos: BlockPos);

        x: number;
        z: number;
        valid_: boolean;

        toString(): string;

        isValid(): boolean;

        tryFixBorder(): boolean;

        removeBorder(): boolean;

        removeBorderCorners(): boolean;
    }
}

