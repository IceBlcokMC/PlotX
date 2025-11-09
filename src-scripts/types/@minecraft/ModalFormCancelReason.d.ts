declare module "@minecraft" {
    export type ModalFormCancelReason = NativeEnum<{
        UserClosed: 0,
        UserBusy: 1,
    }>;
    export const ModalFormCancelReason: ModalFormCancelReason; // fix ts 18042
}
