local _class_cache_ = {}

local _constructor_ = function(meta)
    local instance = {}
    for k, v in pairs(meta) do
        if string.find(k, "__") ~= 1 then
            instance[k] = v
        end
    end
    return instance
end

local _new_index_ = function(t, k, v)
    error("attempt to add new index to meta table")
end

function Class(class_name, class_meta, super_name)
    if class_name == nil then
        error("must specify class name")
    else
        local class = _class_cache_[class_name]
        if class == nil then
            if class_meta == nil then
                error("must specify class meta table")
            else
                if super_name ~= nil then
                    local super = _class_cache_[super_name]
                    if super == nil then
                        error("no class '" .. super_name .. "' cached")
                    else
                        -- create with super
                    end
                else
                    if getmetatable(class_meta) ~= nil then
                        error("attempt to declare class '" .. class_name .. "' with meta table which has metatable")
                    end
                    class_meta.__call = _constructor_
                    class_meta.__newindex = _new_index_
                    setmetatable(class_meta, class_meta)
                    _class_cache_[class_name] = class_meta
                    return class_meta
                end
            end
        else
            if class_meta ~= nil or super_name ~= nil then
                error("attempt to declare a exist class '" .. class_name .. "'")
            end
            return class
        end
    end         
end