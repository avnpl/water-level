export const getHeight = async () => {
  const response = await (await fetch("http://192.168.33.84/")).json();
  return response.distance;
};
