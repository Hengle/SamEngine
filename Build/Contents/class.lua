local _class_cache_ = {}

local _execute_constructor_
_execute_constructor_ = function(instance, class, ...)
    local name = rawget(class, "name")
    local super = rawget(class, "super")
    local constructor = rawget(class, name)
    if super then
        _execute_constructor_(instance, super, ...)
    end
    if constructor then
        constructor(instance, ...)
    end
end

local _class_meta_ = {
    __index = function(class, key)
        local super = rawget(class, "super")
        if super then
            return super[key]
        end
    end,
    __call = function(class, ...)
        local instance = { super = rawget(class, "super") }
        _execute_constructor_(instance, class, ...)
        setmetatable(instance, { __index = class })
        return instance
    end
}

function class(class_name, super_name)
    assert(_class_cache_[class_name] == nil, "class '" .. class_name .. "' already exist")
    local class = {}
    local super
    if super_name ~= nil then
        super = _class_cache_[super_name]
        assert(super, "super class '" .. super_name .. "' do not exist")
    end
    class.name = class_name
    class.super = super
    setmetatable(class, _class_meta_)
    _class_cache_[class_name] = class
    return class
end

function new(name, ...)
    assert(_class_cache_[name], "no class '" .. name .. "'")
    return _class_cache_[name](...)
end

