import circleAssign from 'circle-assign';

let uuidCount = 0

export function create(_ent) {
    const uuid = uuidCount++

    const ent = circleAssign({
        uuid,
        name: "entity " + uuid,
        children: [],
        addChild
    }, _ent)

    function addChild(child) {
        ent.children.push(child)
    }
    return ent
}