import { HasMouseInteraction, HasColor, HasPosition } from "./entity"
import { makeUpdateablePromise } from "./game"

export type easeFunc = (t: number, a: number, b: number, d: number) => number

export const interpolate = (a: number, b: number, d: number, setter: (v: number) => void, fn: easeFunc) => {
    const start = getTime()
    const delta = b - a
    return makeUpdateablePromise<void>(ctx => {
        const cur = getTime()-start
        if(cur < d && !ctx.isCancellationRequested){
            setter(fn(cur, a, delta, d))
        } else {
            setter(b)
            ctx.resolve()
        }
    })
}
export const interpolateVec2 = (a: Vector2, b: Vector2, d: number, setter: (v: Vector2) => void, fn: easeFunc) => {
    const start = getTime()
    const delta = vector2Subtract(b, a)
    return makeUpdateablePromise<void>(ctx => {
        const cur = getTime()-start
        if(cur < d && !ctx.isCancellationRequested){
            const x = fn(cur, a.x, delta.x, d)
            const y = fn(cur, a.y, delta.y, d)
            setter(new Vector2(x,y))
        } else {
            setter(b)
            ctx.resolve()
        }
    })
}

export const waitCondition = (predicate: () => boolean) => makeUpdateablePromise<void>(ctx => {
    if(predicate() || ctx.isCancellationRequested){
        ctx.resolve()
    }
})
export const waitFirst = <T>(list: T[], predicate: (item: T) => boolean) => makeUpdateablePromise<number>(ctx => {
    let idx = list.findIndex(x => predicate(x))
    if(idx !== -1 || ctx.isCancellationRequested) ctx.resolve(idx)
})


export const wait = (time: number) => {
    const start = getTime()
    return waitCondition(() => (getTime()-start) >= time)
} 

export const waitKeyPressed = (key: number) => waitCondition(() => isKeyPressed(key))
export const waitClick = (button: number = MOUSE_BUTTON_LEFT) => waitCondition(() => isMouseButtonDown(button))
export const waitClicked = (entity: HasMouseInteraction) => waitCondition(() => entity.isClicked)
export const waitAnyClicked = (entites: HasMouseInteraction[]) => waitFirst(entites, x => x.isClicked)

export const fadeIn = (c: HasColor, time: number, easeFunc = easeLinearNone) => interpolate(0, 1, time, (v) => c.color = fade(c.color, v), easeFunc)
export const fadeOut = (c: HasColor, time: number, easeFunc = easeLinearNone) => interpolate(1, 0, time, (v) => c.color = fade(c.color, v), easeFunc)
export const move = (p: HasPosition, to: Vector2, time: number, easeFunc = easeLinearNone) => interpolateVec2(p.position, to, time, v2 => p.position = v2, easeFunc)