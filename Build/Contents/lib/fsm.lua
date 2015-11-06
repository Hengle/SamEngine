local machine = {}
machine.__index = machine

local function call_handler(handler, params)
    if handler then
        return handler(table.unpack(params))
    end
end

local function create_transition(name)
    return function(self, ...)
        local can, to = self:can(name)
        if can then
            local from = self.current
            local params = { self, name, from, to, ... }
            if call_handler(self["on_before_" .. name], params) == false
            or call_handler(self["on_leave_" .. from], params) == false then
                return false
            end
            self.current = to
            call_handler(self["on_enter_" .. to] or self["on_" .. to], params)
            call_handler(self["on_after_" .. name] or self["on_" .. name], params)
            call_handler(self["on_state_change"], params)
            return true
        end
        return false
    end
end

local function add_to_map(map, event)
    if type(event.from) == 'string' then
        map[event.from] = event.to
    else
        for _, from in ipairs(event.from) do
            map[from] = event.to
        end
    end
end

function machine.create(options)
    local fsm = {}
    setmetatable(fsm, machine)
    fsm.current = options.initial or 'none'
    fsm.events = {}
    for _, event in ipairs(options.events or {}) do
        local name = event.name
        fsm[name] = fsm[name] or create_transition(name)
        fsm.events[name] = fsm.events[name] or { map = {} }
        add_to_map(fsm.events[name].map, event)
    end
    for name, callback in pairs(options.callbacks or {}) do
        fsm[name] = callback
    end
    return fsm
end

function machine:is(state)
    return self.current == state
end

function machine:can(e)
    local event = self.events[e]
    local to = event and event.map[self.current] or event.map['*']
    return to ~= nil, to
end

function machine:cannot(e)
    return not self:can(e)
end

return machine