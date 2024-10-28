return function(game)
    local colors = game.getComponents("Color")
    local drawables = game.getComponents("Drawable")

    for n in pairs(colors & drawables) do
        colors[n].setColor(255, 0, 0)
    end
end