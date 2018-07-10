function func_Add(x, y)
	local test = CTest:new()
	test:SetData("I'm zz")
	test:GetData()
	return x .. y
end

function func_class(x, y, f)
  f:SetData("I'm zz!");  
--  f:GetData();  
  return f;
end