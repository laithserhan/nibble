local SCREEN_W = 320
local SCREEN_H = 240

local BOOT_ANIM_W = 64
local BOOT_ANIM_H = 64

local SHEET_W = 8

local FRAMES = 32

local SPEED = 12

function init()
    -- Inicializa o serviço de terminal
    --local tty, err = kernel.exec("apps/system/core/terminal.nib", {})

    -- Roda o shell
    --local sh, err = kernel.exec("apps/system/core/shell.nib", {
    --    tty=tostring(tty)
    --})
end

function update(dt)
    start_app("apps/neact.nib", {})
    stop_app(0)

    if clock() > (FRAMES*3/2)/SPEED then
        for i=0,15 do
            swap_colors(i, i)
        end

        --start_app("apps/taskbar.nib", {})
        --start_app("apps/synth.nib", {})
        --stop_app(0)
    end
end

function draw()
    local time = math.floor(clock()*SPEED)
    local frame = math.min(time, FRAMES-1)

    local x, y = frame%SHEET_W*BOOT_ANIM_H, math.floor(frame/SHEET_W)*BOOT_ANIM_H

    if time >= FRAMES+8 then
      local offset = (time-frame-8)*3

        if offset <= 16 then
            for i=offset,15 do
                swap_colors(i, i-(offset-1))
            end
        end
    end

    clear(0)

    if clock() <= (FRAMES*3/2)/SPEED then
      custom_sprite((SCREEN_W-BOOT_ANIM_W)/2, (SCREEN_H-BOOT_ANIM_H)/2, x, y, BOOT_ANIM_W, BOOT_ANIM_H, 0)
    end
end
