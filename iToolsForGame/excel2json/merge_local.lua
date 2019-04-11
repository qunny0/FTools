
-- package.path = "/opt/tankserver/embedded/share/lua/5.2/?.lua;" .. package.path
-- package.cpath = "/opt/tankserver/embedded/lib/lua/5.2/?.so;" .. package.cpath
json = require("cjson")

local info = debug.getinfo(1, "S")
PATH = info.source
PATH = string.sub(PATH, 2, -1)
PATH = string.match(PATH, "^.*/")
print("---PATH:", PATH)

function lua2bigJson(language, pathinfo)

    print('lua2bigJson', package.path);

    local originpath = pathinfo[1]
    local targetname = pathinfo[2]
    local newspecialtarget = pathinfo[3]

    merge_old_files(language,originpath,targetname)
    print(targetname,"   updated")
end

function merge_old_files(language,originpath,targetname)
    local big_json = get_dir_files(language,originpath)
    local data = json.encode(big_json)
    write_file(targetname, data)
end

function file_exists(path)
  local file = io.open(path, "rb")
  if file then file:close() end
  return file ~= nil
end

function get_dir_files(language, dir_path)
    local cmd = "cd "..dir_path.."&& ls"
    local s = io.popen(cmd)
    local fileLists = s:read("*all")
    local big_json = {}
    local start_pos = 0

    while true do
        local nouse,end_pos,file_name = string.find(fileLists, "([^\n\r]+.lua)", start_pos)
        if not end_pos then
            break
        end

        local isNewCfgFile = find_file_by2(file_name)
        if not isNewCfgFile then
            local tmp_file_name = string.sub(file_name, 0, -5)
            if is_need_modify(language, "", tmp_file_name) then
                local big_json_key = string.lower(tmp_file_name)
                local configCfg = require('configCfg')
                if configCfg[tmp_file_name] and configCfg[tmp_file_name][language] then
                    tmp_file_name = language.."."..tmp_file_name
                end

                print('tmp_file_name', tmp_file_name);

                local cfg_file = require(tmp_file_name)
                big_json[big_json_key] = cfg_file

                package.loaded[tmp_file_name] = nil;
            end
        end

        start_pos = end_pos + 1
    end

    return big_json
end

function write_file(file_name,string)
    local f = io.open(file_name, 'w+')
    f:write(string)
    f:close()
end

function get_file(file_name)
    local f = io.open(file_name, 'r')
    local string = f:read("*all")
    f:close()
    return string
end

function get_md5_mark()
    local md5_marks = get_file(cfg_md5_mark_path)
    return json.decode(md5_marks)
end

function is_need_modify(language,file_path, file_name)
    if filter_cfg(file_name) then return false end

    return true
end

function md5(file_path)
    local cmd = "md5sum "..file_path
    local s = io.popen(cmd)
    return s:read("*all")
end

function filter_cfg(file_name)
    local no_write_cfg = {
        baseCfg=1,
        configCfg=1,
        config=1,
        debugCfg=1,
        interfaceCfg=1,
        modelCfg=1,
        responseCfg=1,
        formulaCfg=1,
        initCfg=1,
        gameCfg=1,
        giftby3kCfg=1,
        giftbyFkylcCfg=1,
        giftbyWbCfg=1,
        giftbyzjCfg=1,
        newUserGuidMails=1,
        rechargeCfg=1,
        orderCfg=1,
        responsecfg=1,
        platMappingCfg=1,
        errorCodeCfg=1,
        extraRechargeCfg=1,
        childNameCfg=1,
        lampInfoCfg=1,
    }
    if no_write_cfg[file_name] then return true end
    return false
end

function find_file_by2(file_name)
    local nouse,end_pos,_ = string.find(file_name, "([a-zA-Z]_2)")
    if not end_pos then return false end
    return true
end

function filter_new_cfg(file_name)
    local newConfigCfg = require('newConfigCfg')
    if newConfigCfg[file_name] then return true end
    return false
end

function merge_new_special(language,targetname)
    local newConfigCfg = require('newConfigCfg')
    local newFiles = {}
    for fileName,newInfo in pairs(newConfigCfg) do
        if newInfo[language] then
            newFiles[fileName] = 1
        end
    end

    local newSpecialData = {}
    local configCfg = require('configCfg')
    for fileName,_ in pairs(newFiles) do
        local newFileName = fileName.."_2"

        local fileData
        if configCfg[fileName] and configCfg[fileName][language] then
            fileData = require(language.."."..newFileName)
        else
            fileData = require(newFileName)
        end
        local fileNameLower = string.lower(fileName)
        newSpecialData[fileNameLower]=fileData
    end

    local data = json.encode(newSpecialData)
    write_file(targetname, data)
end


local oldpackagepath = package.path;

local lua_dir = PATH .. '../../../config/Stable'
local target_json_dir = PATH .. '../../../config/json_stable/'
local cfg_md5_mark_path = PATH .. '../tool/cfg_md5_mark'
package.path = lua_dir.."/?.lua;"..oldpackagepath

local mergePath = {
    ['cn'] = {lua_dir, target_json_dir.."gameconfig_cn.json"},
    ['tw'] = {lua_dir, target_json_dir.."gameconfig_tw.json"},
    ['oasis'] = {lua_dir, target_json_dir.."gameconfig_oasis.json"},
}

for language,v in pairs(mergePath) do
    lua2bigJson(language, v)
end

----
local lua_dir_test = PATH .. '../../../config/testing'
local target_json_test_dir = PATH .. '../../../config/json_testing/'
package.path = lua_dir_test.."/?.lua;"..oldpackagepath

local test_mergePath = {
    ['cn'] = {lua_dir_test, target_json_test_dir.."gameconfig_cn.json"},
    ['tw'] = {lua_dir_test, target_json_test_dir.."gameconfig_tw.json"},
    ['oasis'] = {lua_dir_test, target_json_test_dir.."gameconfig_oasis.json"},
}

for language,v in pairs(test_mergePath) do
    lua2bigJson(language, v)
end


---
local lua_dir_version = PATH .. '../../../config/version'
local target_json_version_dir = PATH .. '../../../config/json_version/'
package.path = lua_dir_version.."/?.lua;"..oldpackagepath

local version_mergePath = {
    ['cn'] = {lua_dir_version, target_json_version_dir.."gameconfig_cn.json"},
    ['tw'] = {lua_dir_version, target_json_version_dir.."gameconfig_tw.json"},
    ['oasis'] = {lua_dir_version, target_json_version_dir.."gameconfig_oasis.json"},
}

for language,v in pairs(version_mergePath) do
    lua2bigJson(language, v)
end